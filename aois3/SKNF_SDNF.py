import pprint

def get_str_from_brackets(equation):
    str_from_brackets = []
    i = 0

    while i < len(equation):
        if equation[i] == '(':
            i += 1
            str_ = ""
            while equation[i] != ')':
                str_ += equation[i]
                i += 1
            str_from_brackets.append(str_)
        i += 1

    return str_from_brackets

def get_element(br, i):
    el = br[i]

    if el == '¬':
        el = br[i] + br[i + 1]
        i += 1

    return el, i

def are_equal(bracket1, bracket2):
    str_ = ""
    i = 0
    while i < len(bracket1):
        el, i = get_element(bracket1, i)
        i += 1

        j = 0
        while j < len(bracket2):
            elem, j = get_element(bracket2, j)
            j += 1

            if el == elem:
                str_ += el

    return str_

def remove_not_symbol(str_):
    return str_.replace('¬', '')

def compare_brackets(str_from_brackets):
    equal_el_from_brackets = []
    unique_str = []

    str_from_brackets = [bracket1 for index, bracket1 in enumerate(str_from_brackets)
                         if sum(1 for idx, bracket2 in enumerate(str_from_brackets)
                                if remove_not_symbol(bracket1) == remove_not_symbol(bracket2) and idx != index) > 0]

    for ind, bracket1 in enumerate(str_from_brackets):
        for i in range(ind + 1, len(str_from_brackets)):
            bracket2 = str_from_brackets[i]
            str_ = are_equal(bracket1, bracket2)

            if str_ and len(remove_not_symbol(str_)) == len(remove_not_symbol(bracket1)) - 1:
                equal_el_from_brackets.append(str_)

    combined_array = list(set(unique_str + equal_el_from_brackets))

    return combined_array

def check_compare_brackets(array_to_check):
    result = {}

    for idx, bracket in enumerate(array_to_check):
        another_implicants = [el for index, el in enumerate(array_to_check) if index != idx]
        bracket_letters = list(bracket)

        filtered_implics = ["".join(['1' if letter in bracket_letters else letter for letter in implic]) for implic in another_implicants]

        cleaned_implics = [arr.replace('1', '') for arr in filtered_implics if arr.replace('1', '') != '']

        result[bracket] = " ∨ ".join(cleaned_implics)

        if len(cleaned_implics) == 1 and " ∨ ".join(cleaned_implics) != " ∨ ".join(filtered_implics):
            array_to_check = [item for item in array_to_check if item != bracket]

    return {'проверенные импликанты': result, 'Проверенный массив': array_to_check}

def get_sop(equation):
    resu = ""
    str_from_brackets = get_str_from_brackets(equation)
    equal_el_from_brackets = compare_brackets(str_from_brackets)
    second_loop = compare_brackets(equal_el_from_brackets)
    checked_array = check_compare_brackets(second_loop)
    res = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"

    if not checked_array['Проверенный массив']:
        return "Не удалось вычислить СКНФ"

    for bracket in checked_array['Проверенный массив']:
        terms = list(bracket)
        sop_term = []
        for idx, char in enumerate(terms):
            if char == '1':
                sop_term.append(str_from_brackets[idx])
            elif char == '0':
                sop_term.append(f"¬{str_from_brackets[idx]}")

        resu += "(" + " ∧ ".join(sop_term) + ") ∨ "

    return res

def get_pos(equation):
    resu = ""
    str_from_brackets = get_str_from_brackets(equation)
    equal_el_from_brackets = compare_brackets(str_from_brackets)
    second_loop = compare_brackets(equal_el_from_brackets)
    checked_array = check_compare_brackets(second_loop)
    res = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"

    if not checked_array['Проверенный массив']:
        return "Не удалось вычислить СДНФ"

    for bracket in checked_array['Проверенный массив']:
        terms = list(bracket)
        pos_term = []
        for idx, char in enumerate(terms):
            if char == '0':
                pos_term.append(f"¬{str_from_brackets[idx]}")
            elif char == '1':
                pos_term.append(str_from_brackets[idx])

        resu += "(" + " ∨ ".join(pos_term) + ") ∧ "

    return res

def pretty_print(title, data):
    print(f"\n{title}\n{'-' * len(title)}")
    pprint.pprint(data)

def compare_brackets(str_from_brackets):
    equal_el_from_brackets = []
    unique_str = []

    str_from_brackets = [bracket1 for index, bracket1 in enumerate(str_from_brackets)
                         if sum(1 for idx, bracket2 in enumerate(str_from_brackets)
                                if remove_not_symbol(bracket1) == remove_not_symbol(bracket2) and idx != index) > 0]

    for ind, bracket1 in enumerate(str_from_brackets):
        for i in range(ind + 1, len(str_from_brackets)):
            bracket2 = str_from_brackets[i]
            str_ = are_equal(bracket1, bracket2)

            if str_ and len(remove_not_symbol(str_)) == len(remove_not_symbol(bracket1)) - 1:
                equal_el_from_brackets.append(str_)

    combined_array = list(set(unique_str + equal_el_from_brackets))

    return combined_array

def check_compare_brackets(array_to_check):
    result = {}

    for idx, bracket in enumerate(array_to_check):
        another_implicants = [el for index, el in enumerate(array_to_check) if index != idx]
        bracket_letters = list(bracket)

        filtered_implics = ["".join(['1' if letter in bracket_letters else letter for letter in implic]) for implic in another_implicants]

        cleaned_implics = [arr.replace('1', '') for arr in filtered_implics if arr.replace('1', '') != '']

        result[bracket] = " ∨ ".join(cleaned_implics)

        if len(cleaned_implics) == 1 and " ∨ ".join(cleaned_implics) != " ∨ ".join(filtered_implics):
            array_to_check = [item for item in array_to_check if item != bracket]

    return {'проверенные импликанты': result, 'Проверенный массив': array_to_check}

def get_sop(equation):
    resu = ""
    str_from_brackets = get_str_from_brackets(equation)
    equal_el_from_brackets = compare_brackets(str_from_brackets)
    second_loop = compare_brackets(equal_el_from_brackets)
    checked_array = check_compare_brackets(second_loop)
    res = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"

    if not checked_array['Проверенный массив']:
        return "Не удалось вычислить СКНФ"

    for bracket in checked_array['Проверенный массив']:
        terms = list(bracket)
        sop_term = []
        for idx, char in enumerate(terms):
            if char == '1':
                sop_term.append(str_from_brackets[idx])
            elif char == '0':
                sop_term.append(f"¬{str_from_brackets[idx]}")

        resu += "(" + " ∧ ".join(sop_term) + ") ∨ "

    return res

def get_pos(equation):
    resu = ""
    str_from_brackets = get_str_from_brackets(equation)
    equal_el_from_brackets = compare_brackets(str_from_brackets)
    second_loop = compare_brackets(equal_el_from_brackets)
    checked_array = check_compare_brackets(second_loop)
    res = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"

    if not checked_array['Проверенный массив']:
        return "Не удалось вычислить СДНФ"

    for bracket in checked_array['Проверенный массив']:
        terms = list(bracket)
        pos_term = []
        for idx, char in enumerate(terms):
            if char == '0':
                pos_term.append(f"¬{str_from_brackets[idx]}")
            elif char == '1':
                pos_term.append(str_from_brackets[idx])

        resu += "(" + " ∨ ".join(pos_term) + ") ∧ "

    return res

def calc_method(equation):
    str_from_brackets = get_str_from_brackets(equation)
    equal_el_from_brackets = compare_brackets(str_from_brackets)
    second_loop = compare_brackets(equal_el_from_brackets)
    checked_array = check_compare_brackets(second_loop)

    return {
        'уравнение': equation,
        'упрощенное': str_from_brackets,
        'Этап объединения': equal_el_from_brackets
    }

def table_method(equation):
    str_from_brackets = get_str_from_brackets(equation)
    equal_el_from_brackets = compare_brackets(str_from_brackets)
    second_loop = compare_brackets(equal_el_from_brackets)
    table = get_table(str_from_brackets, second_loop)
    right_implicants = check_table_implicants(table)

    return {'Таблица': table, }

def carno_method(equation):
    str_from_brackets = get_str_from_brackets(equation)
    table = carno_table(str_from_brackets)
    equal_el_from_brackets = compare_brackets(str_from_brackets)
    second_loop = compare_brackets(equal_el_from_brackets)
    checked_array = check_compare_brackets(second_loop)

    return {'Таблица': table}

def carno_table(str_from_brackets):
    replaced = replace_str(str_from_brackets)

    letters = remove_not_symbol(str_from_brackets[0])
    table = [[f"{letters[0]}/{letters[1]}{letters[2]}", "00", "01", "11", "10"], ["0"], ["1"]]

    for i in range(1, len(table)):
        for j in range(1, len(table[0])):
            str_ = table[i][0] + table[0][j]

            if str_ in replaced:
                table[i].append(1)
            else:
                table[i].append(0)

    return table

def replace_str(str_from_brackets):
    changed = []

    for str_ in str_from_brackets:
        new_str = ""
        i = 0

        while i < len(str_):
            if str_[i] == '¬':
                new_str += '0'
                i += 1
            else:
                new_str += '1'
            i += 1

        changed.append(new_str)

    return changed

def check_table_implicants(table):
    right_implicants = []

    for i in range(1, len(table[2])):
        number_ones = {'ones': 0, 'ind': 0}

        for j in range(2, len(table)):
            if table[j][i] == 1:
                number_ones['ones'] += 1
                number_ones['ind'] = j

        if number_ones['ones'] == 1:
            right_implicants.append(table[number_ones['ind']][0])

    return list(set(right_implicants))

def get_table(str_from_brackets, equal_el_from_brackets):
    table = [["", "Конституэнты"], [""] + str_from_brackets]

    for bracket1 in equal_el_from_brackets:
        table_row = [bracket1]
        for bracket2 in str_from_brackets:
            if len(are_equal(bracket1, bracket2)) == len(remove_not_symbol(bracket1)):
                table_row.append(1)
            else:
                table_row.append(0)
        table.append(table_row)

    return table

def pretty_print(title, data):
    print(f"\n{title}\n{'-' * len(title)}")
    pprint.pprint(data)
formula = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"
equation = "(¬abc) ∨ (a¬b¬c) ∨ (a¬bc) ∨ (ab¬c) ∨ (abc)"

calc_result = calc_method(equation)
table_result = table_method(equation)
carno_result = carno_method(equation)

pretty_print("Расчетный метод:", calc_result)
pretty_print("Таблиный метод:", table_result)
pretty_print("Расчетно-табличный метод:", carno_result)

sop = get_sop(equation)
pos = get_pos(equation)
print(f"СКНФ: {sop}")
print(f"СДНФ: {pos}")
