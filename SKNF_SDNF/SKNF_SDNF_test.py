import unittest
from SKNF_SDNF import *
class TestEquationMethods(unittest.TestCase):

    def test_get_str_from_brackets(self):
        equation = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"
        expected = ['¬a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        result = get_str_from_brackets(equation)
        self.assertEqual(result, expected)

    def test_get_element(self):
        bracket = '¬a ∨ ¬b ∨ ¬c'
        el, i = get_element(bracket, 0)
        self.assertEqual(el, '¬a')
        self.assertEqual(i, 1)

        el, i = get_element(bracket, 5)
        self.assertEqual(el, '¬b')
        self.assertEqual(i, 6)

    def test_are_equal(self):
        bracket1 = '¬a ∨ ¬b ∨ ¬c'
        bracket2 = '¬a ∨ b ∨ ¬c'
        result = are_equal(bracket1, bracket2)
        self.assertEqual(result, '¬a ∨ ¬c')

    def test_remove_not_symbol(self):
        str_ = '¬a ∨ ¬b ∨ ¬c'
        result = remove_not_symbol(str_)
        self.assertEqual(result, 'a ∨ b ∨ c')

    def test_compare_brackets(self):
        str_from_brackets = ['¬a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        expected = ['a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        result = compare_brackets(str_from_brackets)
        self.assertEqual(result, expected)

    def test_check_compare_brackets(self):
        array_to_check = ['a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        expected = {
            'проверенные импликанты': {
                'a ∨ ¬b ∨ ¬c': '',
                'a ∨ ¬b ∨ c': '',
                'a ∨ b ∨ ¬c': '',
                'a ∨ b ∨ c': ''
            },
            'Проверенный массив': ['a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        }
        result = check_compare_brackets(array_to_check)
        self.assertEqual(result, expected)

    def test_get_sop(self):
        equation = "(¬abc) ∨ (a¬b¬c) ∨ (a¬bc) ∨ (ab¬c) ∨ (abc)"
        result = get_sop(equation)
        expected = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"
        self.assertEqual(result, expected)

    def test_get_pos(self):
        equation = "(¬abc) ∨ (a¬b¬c) ∨ (a¬bc) ∨ (ab¬c) ∨ (abc)"
        result = get_pos(equation)
        expected = "(¬a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ ¬c) ∧ (a ∨ ¬b ∨ c) ∧ (a ∨ b ∨ ¬c) ∧ (a ∨ b ∨ c)"
        self.assertEqual(result, expected)

    def test_calc_method(self):
        equation = "(¬abc) ∨ (a¬b¬c) ∨ (a¬bc) ∨ (ab¬c) ∨ (abc)"
        result = calc_method(equation)
        expected = {
            'уравнение': equation,
            'упрощенное': ['¬abc', 'a¬b¬c', 'a¬bc', 'ab¬c', 'abc'],
            'Этап объединения': ['a¬b¬c', 'a¬bc', 'ab¬c', 'abc']
        }
        self.assertEqual(result, expected)

    def test_table_method(self):
        equation = "(¬abc) ∨ (a¬b¬c) ∨ (a¬bc) ∨ (ab¬c) ∨ (abc)"
        result = table_method(equation)
        expected = {
            'Таблица': [
                ["", "Конституэнты"],
                ["", "¬abc", "a¬b¬c", "a¬bc", "ab¬c", "abc"],
                ["a¬b¬c", 0, 1, 0, 0, 0],
                ["a¬bc", 0, 0, 1, 0, 0],
                ["ab¬c", 0, 0, 0, 1, 0],
                ["abc", 0, 0, 0, 0, 1]
            ]
        }
        self.assertEqual(result, expected)

    def test_carno_method(self):
        equation = "(¬abc) ∨ (a¬b¬c) ∨ (a¬bc) ∨ (ab¬c) ∨ (abc)"
        result = carno_method(equation)
        expected = {
            'Таблица': [
                ["a/bc", "00", "01", "11", "10"],
                ["0", 1, 0, 0, 0],
                ["1", 0, 0, 0, 1]
            ]
        }
        self.assertEqual(result, expected)

    def test_carno_table(self):
        str_from_brackets = ['¬a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        result = carno_table(str_from_brackets)
        expected = [
            ["a/bc", "00", "01", "11", "10"],
            ["0", 1, 0, 0, 0],
            ["1", 0, 0, 0, 1]
        ]
        self.assertEqual(result, expected)

    def test_replace_str(self):
        str_from_brackets = ['¬a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        result = replace_str(str_from_brackets)
        expected = ['000', '100', '101', '110', '111']
        self.assertEqual(result, expected)

    def test_check_table_implicants(self):
        table = [
            ["a/bc", "00", "01", "11", "10"],
            ["0", 1, 0, 0, 0],
            ["1", 0, 0, 0, 1]
        ]
        result = check_table_implicants(table)
        expected = ['0', '1']
        self.assertEqual(result, expected)

    def test_get_table(self):
        str_from_brackets = ['¬a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        equal_el_from_brackets = ['a ∨ ¬b ∨ ¬c', 'a ∨ ¬b ∨ c', 'a ∨ b ∨ ¬c', 'a ∨ b ∨ c']
        result = get_table(str_from_brackets, equal_el_from_brackets)
        expected = [
            ["", "Конституэнты"],
            ["", "¬a ∨ ¬b ∨ ¬c", "a ∨ ¬b ∨ ¬c", "a ∨ ¬b ∨ c", "a ∨ b ∨ ¬c", "a ∨ b ∨ c"],
            ["a ∨ ¬b ∨ ¬c", 0, 1, 0, 0, 0],
            ["a ∨ ¬b ∨ c", 0, 0, 1, 0, 0],
            ["a ∨ b ∨ ¬c", 0, 0, 0, 1, 0],
            ["a ∨ b ∨ c", 0, 0, 0, 0, 1]
        ]
        self.assertEqual(result, expected)


if __name__ == '__main__':
    unittest.main()
