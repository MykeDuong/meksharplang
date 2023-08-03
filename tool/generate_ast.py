import sys

def main():
    n = len(sys.argv)
    if (n != 2):
        print("Usage: python3 generate_ast.py <output directory>")
        exit(0)
    
    output_dir = sys.argv[1]

    types = {
        "Binary": [["Expr*", "left"], ["Token*", "op"], ["Expr*", "right"]],
        "Ternary": [
            ["Expr*", "firstExpr"], 
            ["Token*", "firstOp"], 
            ["Expr*", "secondExpr"], 
            ["Token*", "secondOp"],
            ["Expr*", "thirdExpr"],
        ],
        "Grouping": [["Expr*", "expr"]],
        "Literal": [["LiteralValue*", "value"]],
        "Unary": [["Token*", "op"], ["Expr*", "right"]]
    }

    define_ast(output_dir, "Expr", types) 
    define_visitor(output_dir, "Expr", types)    

def define_ast(output_dir, base, types):
    for t in types:
        cppDir = output_dir + "/" + t + ".cpp"
        headerDir = output_dir + "/include/" + t + ".h"
        write_cpp(cppDir, base, t, types[t])
        write_header(headerDir, base, t, types[t])

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
    f.write(") : ")
    
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

def write_header(output_dir, base, class_name, fields):
    f = open(output_dir, "w")
    f.write("#ifndef " + class_name.upper() + "_H\n" )
    f.write("#define " + class_name.upper() + "_H\n" )
    f.write("\n")
    f.write('#include "./' + base + '.h"\n' )
    f.write('#include "./Token.h"\n')
    f.write('#include "./LiteralValue.h"\n')
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

def define_visitor(output_dir, base, types):
    f = open(output_dir + "/include/Visitor.h", "w");
    f.write("#ifndef VISITOR_H\n" )
    f.write("#define VISITOR_H\n" )
    f.write("\n")
    for t in types:
        f.write('#include "./' + t + '.h"\n')
    f.write("namespace " + base + " {\n")
    f.write("  class Visitor {\n")
    f.write("    public:\n")
    for t in types:
        f.write("      virtual void visit(const " + t + "* " + t.lower() + ") = 0;\n")
    f.write("    };\n")
    f.write("};\n")
    f.write('\n')
    f.write("#endif\n")

main()
