def calculate(expression):
    try:
        result = eval(expression)
    except:
        print ('Eval error!')
        return None
    return result
