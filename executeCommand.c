#include "executeCommand.h"


ExecuteResult execute_statement(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    switch (statement->type)
    {
    case (STATEMENT_INSERT):
        return execute_insert(input_buffer, statement, table);
    case (STATEMENT_SELECT):
        return execute_select(input_buffer, statement, table);
    case (STATEMENT_EXIT):
        return execute_exit(input_buffer, statement, table);
    }
}

ExecuteResult execute_insert(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &(statement->row_to_insert);
    Cursor *cursor = table_end(table);
    serialize_row(row_to_insert, cursor_value(cursor));
    table->num_rows += 1;
    free(cursor);
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    Row row;
    Cursor *cursor = table_start(table);
    while(!(cursor)->end_of_table)
    {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }
    return EXECUTE_SUCCESS;
    free(cursor);
}

ExecuteResult execute_exit(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    close_buffer(input_buffer);
    close_db(table);
    exit(EXIT_SUCCESS);
}