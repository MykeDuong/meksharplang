import sys

def main():
    n = len(sys.argv)
    if (n != 2):
        print("Usage: python3 generate_ast.py <output directory>")
        exit(0)
    
    output_dir = sys.argv[1]

    expr_types = {
        "FunctionExpr": [["std::vector<Token*>", "params"], ["std::vector<Stmt::Stmt*>", "body"]],
        "Assign": [["Token*", "name",], ["Expr*", 'value']],
        "Binary": [["Expr*", "left"], ["Token*", "op"], ["Expr*", "right"]],
        "Call": [["Expr*", "callee"], ["Token*", "paren"], ["std::vector<Expr*>", "arguments"]],
        "Ternary": [
            ["Expr*", "firstExpr"], 
            ["Token*", "firstOp"], 
            ["Expr*", "secondExpr"], 
            ["Token*", "secondOp"],
            ["Expr*", "thirdExpr"],
        ],
        "Grouping": [["Expr*", "expr"]],
        "Literal": [["LiteralValue*", "value"]],
        "Logical": [["Expr*", "left"], ["Token*", "op"], ["Expr*", "right"]],
        "Unary": [["Token*", "op"], ["Expr*", "right"]],
        "Array": [["std::vector<Expr*>", "elements"], ["Token*", "square"]],
        "ArrayElement": [["Expr*", "callee"], ["Expr*", "index"], ["Token*", "square"]],
        "Variable": [["Token*", "name"]],
        "dep" : []
    }
    
    stmt_types = {
        "Block": [["std::vector<Stmt*>", "statements"]],
        "ClassStmt": [["Token*", "name"], ["std::vector<Function*>", "methods"]],
        "Expression": [["Expr::Expr*", "expression"]],
        "Function": [["Token*", "name"], ["Expr::FunctionExpr*", "function"]],
        "IfStmt": [["Expr::Expr*", "condition"], ["Stmt*", "thenBranch"], ["Stmt*", "elseBranch"]],
        "Print": [["Expr::Expr*", "expression"]],
        "Var": [["Token*", "name"], ["Expr::Expr*", "initializer"]],
        "WhileStmt": [["Expr::Expr*", "condition"], ["Stmt*", "body"]],
        "BreakStmt": [["Token*", "keyword"]],
        "ReturnStmt": [["Token*", "keyword"], ["Expr::Expr*", "value"]],
        "dep": ["Expr"]
    }

    info =  { "Expr" : expr_types, "Stmt": stmt_types }

    define_ast(output_dir, info) 
    define_visitor(output_dir, info)

def define_ast(output_dir, info):
    for base in info:
        types = info[base]
        dep = types["dep"]
        for t in types:
            if t == "dep": continue
            cppDir = output_dir + "/" + t + ".cpp"
            headerDir = output_dir + "/include/" + t + ".h"
            write_cpp(cppDir, base, t, types[t])
            write_header(headerDir, base, t, types[t], dep)

def write_cpp(output_dir, base, class_name, fields):
    f = open(output_dir, "w")

    f.write('#include "./include/' + class_name + '.h"\n\n');
    f.write('#include "./include/Visitor.h"\n')
    f.write("using namespace " + base + ';\n\n')
    f.write(class_name + "::" + class_name + "(")
    for i, field in enumerate(fields):
        f.write('const ' + field[0] + " " + field[1])
        if i != len(fields) - 1:
            f.write(', ')
    f.write(") ")
    
    if len(fields) > 0:
        f.write(": ")
    
    for i, field in enumerate(fields):
        f.write(field[1] + '(' + field[1] + ')')
        if i != len(fields) - 1:
            f.write(', ')
   
    f.write(' {}\n')
    f.write('\n')
    f.write("void const " + class_name + "::accept(Visitor* visitor) const {\n")
    f.write("  visitor->visit(this);\n")
    f.write("}")

    f.close()

def write_header(output_dir, base, class_name, fields, dep):
    f = open(output_dir, "w")
    f.write("#ifndef " + class_name.upper() + "_H\n" )
    f.write("#define " + class_name.upper() + "_H\n" )
    f.write("\n")
    f.write('#include "./' + base + '.h"\n' )
    
    # Edge cases
    if base == "Expr" and class_name == "FunctionExpr":
        f.write('#include "./Stmt.h"\n')
    if base == "Stmt" and class_name == "Function":
        f.write('#include "./FunctionExpr.h"\n')
    if base == "Stmt" and class_name == "ClassStmt":
        f.write('#include "./Function.h"\n')

    for d in dep:
        f.write('#include "./' + d + '.h"\n')
    f.write('#include "./Token.h"\n')
    f.write('#include "./LiteralValue.h"\n')
    f.write('#include <vector>\n')
    f.write('\n')

    f.write("namespace " + base + " {\n")
    f.write("  class " + base + ";\n")
    f.write("  class " + class_name + ": public " + base +" {\n")
    f.write("    public:\n")
    for field in fields:
        f.write("      const " + field[0] + " " + field[1] + ";\n")
    f.write("\n")
    #f.write("    public:\n")
    f.write("      " + class_name + "(")
    for i, field in enumerate(fields):
        f.write("const " + field[0] + " " + field[1])
        if i != len(fields) - 1:
            f.write(', ')
    f.write(");\n")
    f.write("      void const accept(Visitor* visitor) const;\n")
    f.write("  };\n")
    f.write("};\n")
    f.write('\n')
    f.write("#endif\n")


    f.close()

def define_visitor(output_dir, info):
    f = open(output_dir + "/include/Visitor.h", "w");
    f.write("#ifndef VISITOR_H\n" )
    f.write("#define VISITOR_H\n" )
    f.write("\n")
    for base in info:
        types = info[base]
        for t in types:
            if t == 'dep': continue;
            f.write('#include "./' + t + '.h"\n')
    for base in info:
        f.write("namespace " + base + " {\n")
        f.write("  class Visitor {\n")
        f.write("    public:\n")
        types = info[base]
        for t in types:
            if t == 'dep': continue;
            f.write("      virtual void visit(const " + t + "* " + t.lower() + ") = 0;\n")
        f.write("    };\n")
        f.write("};\n")
        f.write('\n')
    f.write("\n")
    f.write("#endif\n")

main()
