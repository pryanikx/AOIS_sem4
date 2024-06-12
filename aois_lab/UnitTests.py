import unittest
from unittest.mock import patch
from Formula import LogicFunction
from calculation import *
from McCluskey import *
from Karno_table import *


class TestLogicFunction(unittest.TestCase):

    def setUp(self):
        self.lf = LogicFunction()

    def test_handler_input_formula(self):
        self.lf.handler_input_formula('x1 * x2 + !x3')
        self.assertEqual(self.lf.logic_formula, 'x1  and  x2  or   not x3')
        self.assertEqual(sorted(self.lf.arguments), ['x1', 'x2', 'x3'])

    def test_replace_implication(self):
        self.lf.handler_input_formula('x1 * x2 => x3')
        self.lf.replace_implication()
        self.assertEqual(self.lf.logic_formula, 'x1 and (not( x2) ) or x3')

    def test_sort_argument(self):
        self.lf.arguments = {'x3', 'x1', 'x2'}
        self.lf.arguments = list(self.lf.arguments)  # Convert set to list for sorting
        self.lf.sort_argument()
        self.assertEqual(self.lf.arguments, ['x1', 'x2', 'x3'])

    def test_replace_argument_on_number(self):
        self.lf.arguments = ['x1', 'x2']
        self.lf.temp_logic_formula = 'x1 and x2 or not x1'
        self.lf.replace_argument_on_number([1, 0])
        self.assertEqual(self.lf.temp_logic_formula, '1 and 0 or not 1')

    def test_create_logic_table(self):
        self.lf.handler_input_formula('x1 * x2')
        self.lf.create_logic_table()
        expected_rows = [
            [0, 0, 0, 0, 8],
            [0, 1, 0, 0, 4],
            [1, 0, 0, 0, 2],
            [1, 1, 1, 1, 1],
        ]
        actual_rows = [row for row in self.lf.table_object._rows]
        self.assertEqual(actual_rows, expected_rows)

    def test_perfect_conjunctive_normal_form(self):
        self.lf.handler_input_formula('x1 * x2')
        self.lf.create_logic_table()
        self.lf.perfect_conjunctive_normal_form()
        self.assertEqual(self.lf.perfect_conjunctive_normal_form_formula, '( x1 + x2 )*( x1 + !x2 )*( !x1 + x2 )')

    def test_perfect_disjunctive_normal_form(self):
        self.lf.handler_input_formula('x1 + x2')
        self.lf.create_logic_table()
        self.lf.perfect_disjunctive_normal_form()
        self.assertEqual(self.lf.perfect_disjunctive_normal_form_formula, '( !x1 * x2 )+( x1 * !x2 )+( x1 * x2 )')

    def test_translate_in_decimal(self):
        self.lf.arguments = ['x1', 'x2']
        result = self.lf.translate_in_decimal([0], '01*10')
        self.assertEqual(result, [1, 2])

    def test_calculate_ratio(self):
        self.lf.handler_input_formula('x1 * x2')
        self.lf.create_logic_table()
        self.lf.calculate_ratio()
        self.assertEqual(self.lf.number_ratio, 1)

    def test_glue_implicants(self):
        formula = '(x1*x2)+(!x1*x3)'
        expected_result = ([['(x1*x2)+(!x1*x3)']], [['(x1*x2)+(!x1*x3)']], 'pdnf')
        self.assertEqual(glue_implicants(formula), expected_result)

    def test_calaculation_method(self):
        formula = '(x1+x2)*(x3+!x4)'
        expected_result = [['(x1+x2)*(x3+!x4)']]
        self.assertEqual(calaculation_method(formula), expected_result)

    def test_delete_extra_arguments(self):
        formula = ['x1', '!x1', 'x2']
        expected_result = [['x2']]
        self.assertEqual(delete_extra_arguments(formula), expected_result)

    def test_check_size(self):
        formula = [['x1', 'x2'], ['x3', 'x4']]
        self.assertTrue(check_size(formula))

    def test_connect_two_implicats(self):
        formula = [['x1', 'x2'], ['!', 'x1', 'x2']]
        expected_result = ([['x1', 'x2'], ['!', 'x1', 'x2']], [['x1', 'x2'], ['!', 'x1', 'x2']], 'pdnf')
        self.assertEqual(connect_two_implicats(formula, 'pdnf'), expected_result)

    def test_connect_arguments(self):
        first_implicat = ['x1', 'x2']
        second_implicant = ['x1', '!', 'x2']
        expected_result = ['x1']
        self.assertEqual(connect_arguments(first_implicat, second_implicant), expected_result)

    def test_replace_arguments_on_0_1_pdnf(self):
        temp_formula = [['x1', '!x2']]
        current_implicat = 0
        formula = [['x1', '!x2']]
        expected_result = ([['1', '1']], {'x1': '1', '!x2': '1', '!x1': '0', 'x2': '0'})
        self.assertEqual(replace_arguments_on_0_1_pdnf(temp_formula, current_implicat, formula), expected_result)

    def test_replace_arguments_on_0_1_pcnf(self):
        temp_formula = [['x1', '!x2']]
        current_implicat = 0
        formula = [['x1', '!x2']]
        expected_result = ([['0', '0']], {'x1': '0', '!x2': '0', '!x1': '1', 'x2': '1'})
        self.assertEqual(replace_arguments_on_0_1_pcnf(temp_formula, current_implicat, formula), expected_result)

    def test_remove_extra_implications(self):
        formula = [['x1', 'x2'], ['x1', '!x2'], ['!', 'x1', 'x2'], ['!', 'x1', '!x2']]
        expected_result = [['x1', 'x2'], ['x1', '!x2'], ['!', 'x1', 'x2'], ['!', 'x1', '!x2']]
        self.assertEqual(remove_extra_implications(formula, 'pdnf'), expected_result)

    def test_check_on_extra_implicants_pdnf(self):
        cut_back_formula = ['x1', '!x1']
        self.assertTrue(check_on_extra_implicants_pdnf(cut_back_formula))

    def test_check_on_extra_implicants_pcnf(self):
        cut_back_formula = ['x1', '!x1']
        self.assertTrue(check_on_extra_implicants_pcnf(cut_back_formula))

    def test_cut_back_arguments(self):
        temp_formula = [['1', '0'], ['x1', '!x2']]
        self.assertTrue(cut_back_arguments(temp_formula, 'pdnf'))

    def test_translate_in_pcnf(self):
        formula = [['x1', 'x2'], ['!', 'x1', 'x2']]
        self.assertEqual(translate_in_pcnf(formula), None)

    def test_translate_in_pdnf(self):
        formula = [['x1', 'x2'], ['!', 'x1', 'x2']]
        self.assertEqual(translate_in_pdnf(formula), None)

    def test_logic_and(self):
        self.assertEqual(logic_and('x1', 'x1'), 'x1')
        self.assertEqual(logic_and('1', '0'), '0')

    def test_logic_or(self):
        self.assertEqual(logic_or('x1', 'x1'), 'x1')
        self.assertEqual(logic_or('1', '0'), '1')

    def test_tabular_calculation_method(self):
        formula_after_glue = [['x1', 'x2'], ['x1', 'x3']]
        base_formula = [['x1', 'x2', 'x3'], ['x1', '!x2', 'x3']]
        form_of_formula = 'pdnf'
        result = tabular_calculation_method(formula_after_glue, base_formula, form_of_formula)
        expected = [['x1', 'x3']]
        self.assertEqual(result, expected)

    def test_delete_duplicate(self):
        formula_after_glue = [['x1', 'x2'], ['x1', 'x2'], ['x2', 'x3']]
        result = delete_duplicate(formula_after_glue)
        expected = [['x1', 'x2'], ['x2', 'x3']]
        self.assertEqual(result, expected)

    def test_implicats_table(self):
        formula_after_glue = [['x1', 'x2'], ['x1', 'x3']]
        base_formula = [['x1', 'x2', 'x3'], ['x1', '!x2', 'x3']]
        with unittest.mock.patch('builtins.print') as mock_print:
            implicats_table(formula_after_glue, base_formula)
            mock_print.assert_called()

    def test_delete_row(self):
        table_data = [['X', '', ''], ['', 'X', 'X']]
        result = delete_row(table_data)
        self.assertEqual(result, None)

    def test_delete_row_no_deletion(self):
        table_data = [['X', '', ''], ['X', 'X', '']]
        result = delete_row(table_data)
        self.assertIsNone(result)

    def test_delete_row_multiple_possible_deletions(self):
        table_data = [['X', '', 'X'], ['', 'X', 'X']]
        result = delete_row(table_data)
        self.assertEqual(result, None)

    def test_table_method(self):
        formula = [['x1', 'x2'], ['x1', 'x3']]
        base_formula = [['x1', 'x2', 'x3'], ['x1', '!x2', 'x3']]
        form_of_formula = 'pdnf'
        amount_values = ['x1', 'x2', 'x3']
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}, {0: 1, 1: 0, 2: 1, 'i': 'x1!x2', 'f': 1}]
        result = table_method(formula, base_formula, form_of_formula, amount_values, table_data)
        expected = [['x1', 'x2']]
        self.assertEqual(result, expected)

    def test_create_table(self):
        amount_values = ['x1', 'x2', 'x3']
        formula = [['x1', 'x2'], ['x1', 'x3']]
        form_of_formula = 'pdnf'
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}, {0: 1, 1: 0, 2: 1, 'i': 'x1!x2', 'f': 1}]
        result = create_table(amount_values, formula, table_data, form_of_formula)
        expected = [[(0, 'x1x2'), (1, 'x1!x2')]]
        self.assertEqual(result, expected)

    def test_transform_dict_for_table(self):
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}]
        result = transform_dict_for_table(table_data)
        expected = [[{0: 0, 1: 1, 2: 1}, 1]]
        self.assertEqual(result, expected)

    def test_transform_dict_in_list(self):
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}]
        result = transform_dict_in_list(table_data)
        expected = [[0, 1, 1]]
        self.assertEqual(result, expected)

    def test_create_line(self):
        amount_arguments = 2
        values = ['x1', 'x2']
        result = create_line(amount_arguments, values)
        expected = [{'x1': 0, 'x2': 0}, {'x1': 1, 'x2': 0}, {'x1': 0, 'x2': 1}, {'x1': 1, 'x2': 1}]
        self.assertEqual(result, expected)

    def test_minimize_function(self):
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}, {0: 1, 1: 0, 2: 1, 'i': 'x1!x2', 'f': 1}]
        form_of_formula = 'pdnf'
        result = minimize_function(table_data, form_of_formula)
        expected = [[(0, 'x1x2'), (1, 'x1!x2')]]
        self.assertEqual(result, expected)

    def test_choose_group(self):
        group_result = [[(0, 'x1x2'), (1, 'x1!x2')]]
        array_of_groups = [[]]
        current_element = (0, 'x1x2')
        choose_group(group_result, array_of_groups, current_element)
        expected = [[(0, 'x1x2'), (1, 'x1!x2')]]
        self.assertEqual(array_of_groups, expected)

    def test_check_one_group(self):
        table_data = [[(0, 'x1x2'), (1, 'x1!x2')]]
        current_row = 0
        current_column = 0
        form_of_formula = 'pdnf'
        result = check_one_group(table_data, current_row, current_column, form_of_formula)
        expected = [False, False, True, False]
        self.assertEqual(result, expected)

    def test_check_two_group(self):
        table_data = [[(0, 'x1x2'), (1, 'x1!x2')]]
        current_row = 0
        current_column = 0
        form_of_formula = 'pdnf'
        result = check_two_group(table_data, current_row, current_column, form_of_formula)
        expected = []
        self.assertEqual(result, expected)

    def test_check_four_group(self):
        table_data = [[(0, 'x1x2'), (1, 'x1!x2')]]
        current_row = 0
        current_column = 0
        form_of_formula = 'pdnf'
        result = check_four_group(table_data, current_row, current_column, form_of_formula)
        expected = []
        self.assertEqual(result, expected)

    def test_check_four_group_in_square(self):
        table_data = [[(0, 'x1x2'), (1, 'x1!x2')]]
        current_row = 0
        current_column = 0
        form_of_formula = 'pdnf'
        result = check_four_group_in_square(table_data, current_row, current_column, form_of_formula)
        expected = []
        self.assertEqual(result, expected)

    def test_build_implicants(self):
        data_about_argument = {}
        current_element = [(0, 'x1x2'), (1, 'x1!x2')]
        result = build_implicants(data_about_argument, current_element)
        expected = {'x1': (True, 'x'), 'x2': (True, 'x')}
        self.assertEqual(result, expected)

    def test_check_all_in_group(self):
        table_data = [[(0, 'x1x2'), (1, 'x1!x2')]]
        form_of_formula = 'pdnf'
        result = check_all_in_group(table_data, form_of_formula)
        expected = False
        self.assertEqual(result, expected)

    def test_build_pdnf(self):
        group_of_arguments = [[(0, 'x1x2'), (1, 'x1!x2')]]
        result = build_pdnf(group_of_arguments)
        expected = [['x1', 'x2']]
        self.assertEqual(result, expected)

    def test_build_pcnf(self):
        group_of_arguments = [[(0, 'x1x2'), (1, 'x1!x2')]]
        result = build_pcnf(group_of_arguments)
        expected = [['x1', '!x2']]
        self.assertEqual(result, expected)

    def test_tabular_calculation_methodd(self):
        formula_after_glue = [['x1', 'x2'], ['x1', '!x2']]
        base_formula = [['x1', 'x2', 'x3'], ['x1', '!x2', 'x3']]
        form_of_formula = 'pdnf'
        result = tabular_calculation_method(formula_after_glue, base_formula, form_of_formula)
        expected = [['x1', 'x2']]
        self.assertEqual(result, expected)

    def test_delete_duplicatee(self):
        formula_after_glue = [['x1', 'x2'], ['x1', '!x2'], ['x1', 'x2']]
        result = delete_duplicate(formula_after_glue)
        expected = [['x1', 'x2'], ['x1', '!x2']]
        self.assertEqual(result, expected)

    def test_implicats_tablee(self):
        formula_after_glue = [['x1', 'x2'], ['x1', '!x2']]
        base_formula = [['x1', 'x2', 'x3'], ['x1', '!x2', 'x3']]
        result = implicats_table(formula_after_glue, base_formula)
        expected = [['x1', 'x2']]
        self.assertEqual(result, expected)

    def test_delete_roww(self):
        table_data = [[0, 1, 1, 'x1x2', 1], [1, 0, 1, 'x1!x2', 1]]
        result = delete_row(table_data)
        expected = None
        self.assertEqual(result, expected)

    def test_create_tablee(self):
        amount_values = ['x1', 'x2', 'x3']
        formula = [['x1', 'x2'], ['x1', 'x3']]
        form_of_formula = 'pdnf'
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}, {0: 1, 1: 0, 2: 1, 'i': 'x1!x2', 'f': 1}]
        result = create_table(amount_values, formula, table_data, form_of_formula)
        expected = [[(0, 'x1x2'), (1, 'x1!x2')]]
        self.assertEqual(result, expected)

    def test_transform_dict_for_tablee(self):
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}]
        result = transform_dict_for_table(table_data)
        expected = [[{0: 0, 1: 1, 2: 1}, 1]]
        self.assertEqual(result, expected)

    def test_transform_dict_in_listt(self):
        table_data = [{0: 0, 1: 1, 2: 1, 'i': 'x1x2', 'f': 1}]
        result = transform_dict_in_list(table_data)
        expected = [[0, 1, 1]]
        self.assertEqual(result, expected)

    def test_create_linee(self):
        amount_arguments = 2
        values = ['x1', 'x2']
        result = create_line(amount_arguments, values)
        expected = [{'x1': 0, 'x2': 0}, {'x1': 1, 'x2': 0}, {'x1': 0, 'x2': 1}, {'x1': 1, 'x2': 1}]
        self.assertEqual(result, expected)

    def test_minimize_functionn(self):
        table_data = [[(0, 'x1x2'), (1, 'x1!x2')]]
        form_of_formula = 'pdnf'
        result = minimize_function(table_data, form_of_formula)
        expected = [[(0, 'x1x2'), (1, 'x1!x2')]]
        self.assertEqual(result, expected)

    def test_check_all_in_groupp(self):
        table_data = [[(0, 'x1x2'), (1, 'x1!x2')]]
        form_of_formula = 'pdnf'
        result = check_all_in_group(table_data, form_of_formula)
        expected = False
        self.assertEqual(result, expected)

    def test_build_pdnff(self):
        group_of_arguments = [[(0, 'x1x2'), (1, 'x1!x2')]]
        result = build_pdnf(group_of_arguments)
        expected = [['x1', 'x2']]
        self.assertEqual(result, expected)

    def test_build_pcnff(self):
        group_of_arguments = [[(0, 'x1x2'), (1, 'x1!x2')]]
        result = build_pcnf(group_of_arguments)
        expected = [['x1', '!x2']]
        self.assertEqual(result, expected)


if __name__ == '__main__':
    unittest.main()