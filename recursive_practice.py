"""
Fungsi rekursif akan banyak dipakai di pengembangan bagian interpreter berikutnya.
Jadi, saya butuh memahaminya dengan benar, maka itu saya akan berhenti sejenak
untuk berlatih mengenai topik ini menggunakan beberapa kode Python di bawah ini.
"""
def sum(arr: list) -> int:
    total = 0
    for elm in arr:
        if isinstance(elm, list):
            total += sum(elm)
        else:
            if elm % 2 == 0: total += elm
            
    return total

nested_arr = [1, 2, [3, 4], 5, [6, 7, [8, 9], 10], 11]
print("total dari semua bilangan genap di [1, 2, [3, 4], 5, [6, 7, [8, 9], 10], 11] = ", sum(nested_arr))

def eval(expr: list) -> int:
    """
    TODO
    """
    op = expr[0]
    first_operand = expr[1]
    second_operand = expr[2]
    first = eval(first_operand) if isinstance(first_operand, list) else first_operand
    second = eval(second_operand) if isinstance(second_operand, list) else second_operand

    if op == "+":
        return first + second
    elif op == "-":
        return first - second
    elif op == "*":
        return first * second
    elif op == "/":
        return first / second
    elif op == "%":
        return first % second
    
    raise Exception("Sorry, operation undefined or still not yet supported")
        
expr = ["+", 10, ["+", 4, ["*", 3, 3]]]
print("(+ 10 (+ 4 (* 3 3))) = ", eval(expr))

"""
(+ 3 4 5 (* 10 (% 11 3)))

       +
     / | | \
    3  4  5  *
           /  \
         10    %
              / \
            11   3
"""
ct = ["+", 
    3, 
    4, 
    5, 
    ["*", 
        10, 
        ["%", 11, 3]
    ]
]

def eval_v2(expr: list) -> int:
    op = expr[0]
    first_operand = expr[1]
    first = eval_v2(first_operand) if isinstance(first_operand, list) else first_operand

    for rest in expr[2:]:
        if op == "+":
            first += eval_v2(rest) if isinstance(rest, list) else rest
        elif op == "-":
            first -= eval_v2(rest) if isinstance(rest, list) else rest
        elif op == "*":
            first *= eval_v2(rest) if isinstance(rest, list) else rest
        elif op == "/":
            first /= eval_v2(rest) if isinstance(rest, list) else rest
        elif op == "%":
            first %= eval_v2(rest) if isinstance(rest, list) else rest
        else:
            raise Exception("Sorry, operation undefined or still not yet supported", op)
    
    return first
    

print("(+ 3 4 5 (* 10 (% 11 3))) = ", eval_v2(ct))

ct2 = ["+", 
    1, 
    2, 
    3,
    ["/", 4, 2], 
    ["*", 
        10, 
        ["/", 11, 3]
    ]
]

print("(+ 1 2 3 (/ 4 2) (* 10 (/ 11 3))) = ", eval_v2(ct2))


"""
mencoba mengggunakan tree class untuk operasi yg sama
(+ 3 4 5 (* 10 (% 11 3)))

       +
     / | | \
    3  4  5  *
           /  \
         10    %
              / \
            11   3
"""
class Tree:
    def __init__(self, label, branches=[]):
        self.label = label
        for branch in branches:
            assert isinstance(branch, Tree)
        self.branches = list(branches)
    
    def __repr__(self):
        if self.branches:
            branch_str = ", " + repr(self.branches)
            return f"Tree({repr(self.label)}{branch_str})"
        return f"Tree({repr(self.label)})"
    
    def is_leaf(self):
        return not self.branches

def eval_rt(expr: Tree) -> int:
    # jika tidak memiliki branch, maka dia number
    if expr.is_leaf():
        return expr.label
    
    # jika memiliki branch, label pasti operator
    op = expr.label
    first_operand = expr.branches[0]
    first = eval_rt(first_operand) if not first_operand.is_leaf() else first_operand.label
    for b in expr.branches[1:]:
        if op == "+":
            first += eval_rt(b) if not b.is_leaf() else b.label
        elif op == "-":
            first -= eval_rt(b) if not b.is_leaf() else b.label
        elif op == "*":
            first *= eval_rt(b) if not b.is_leaf() else b.label
        elif op == "/":
            first /= eval_rt(b) if not b.is_leaf() else b.label
        elif op == "%":
            first %= eval_rt(b) if not b.is_leaf() else b.label
        else:
            raise Exception("Sorry, operation undefined or still not yet supported", op)
        
    return first

rt = Tree(
    "+",
    [
        Tree(3), Tree(4), Tree(5), 
        Tree("*", 
            [
                Tree(10), 
                Tree("+", [Tree(5), Tree(5)])
            ]
        )
    ]
)

print(rt, " = ", eval_rt(rt))