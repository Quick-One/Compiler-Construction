/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#include "lexerDef.h"

static State states[MAX_STATES];
static trie look_up_table;

// create a new transition
transition f(char ch, state_id next_state)
{
    transition t = (transition)malloc(sizeof(Transition));
    t->next_state = &states[next_state];
    t->next_char = ch;
    return t;
}

// create a transition for a to z except b to d
transition *aToZExceptBToD(state_id next_state)
{
    int size = 23;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        if (i != 'b' && i != 'c' && i != 'd')
        {
            transitions[j++] = f(i, next_state);
        }
    }
    return transitions;
}

// create a transition for a to z
transition *aToZ(state_id next_state)
{
    int size = 26;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    return transitions;
}

// create a transition for A to Z
transition *AToZ(state_id next_state)
{
    int size = 52;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'a'; i <= 'z'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    for (int i = 'A'; i <= 'Z'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    return transitions;
}

// create a transition for b to d
transition *bToD(state_id next_state)
{
    int size = 3;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 'b'; i <= 'd'; i++)
    {
        transitions[j++] = f(i, next_state);
    }
    return transitions;
}

// create a transition for 0 to 9
transition *zeroToNine(state_id next_state)
{
    int size = 10;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        transitions[j++] = f(i + '0', next_state);
    }
    return transitions;
}

// create a transition for 2 to 7
transition *twoToSeven(state_id next_state)
{
    int size = 6;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int j = 0;
    for (int i = 0; i < 6; i++)
    {
        transitions[j++] = f(i + '2', next_state);
    }
    return transitions;
}

// Add remaining transitions to the graph
void theta(state_id curr_state, state_id next_state)
{
    int size = ALPHABET_SIZE - states[curr_state].length;
    transition *transitions = (transition *)malloc(size * sizeof(transition));
    int count = 0;
    int *freq = (int *)calloc(128, sizeof(int));
    for (int j = 0; j < states[curr_state].length; j++)
    {
        freq[states[curr_state].transitions[j]->next_char] = 1;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (freq[ALPHABETS[i]] != 1)
        {
            transitions[count++] = f(ALPHABETS[i], next_state);
        }
    }
    add_transition(curr_state, transitions, size);
}


// Returns a New Token with a given token_id, line count and lexeme
token getNewToken(token_id id, int lc, char *lexeme)
{
    token newToken = (token)malloc(sizeof(Token));
    newToken->tk = id;
    newToken->lc = lc;
    // HARDCODED LEXEME SIZE TO 30?!
    // CARE THIS MIGHT CAUSE SEGMENTATION FAULT 
    newToken->lexeme = (char *)(malloc(200 * sizeof(char)));
    memset(newToken->lexeme, '\0', 200);
    strncpy(newToken->lexeme, lexeme, strlen(lexeme));
    return newToken;
}

// Adds transitions to the state
void add_transition(state_id state, transition *transitions, int transition_count)
{
    int new_length = states[state].length + transition_count;
    states[state].transitions = (transition *)realloc(states[state].transitions, new_length * sizeof(transition));
    for (int i = 0; i < transition_count; i++)
    {
        states[state].transitions[states[state].length + i] = transitions[i];
    }
    states[state].length = new_length;
}

// Initializes the states of the DFA
void initialize_states()
{
    for (int i = 0; i < MAX_STATES; i++)
    {
        states[i].length = 0;
        states[i].state_id = i;
        states[i].retract_count = 0;
        states[i].token = -1;
        states[i].transitions = NULL;
    }
    states[INVALID].token = TK_INVALID;
     states[S_60].token = TK_COMMENT;
    states[S_2].token = TK_NOTOKEN;
    states[S_3].token = TK_NOTOKEN;
    states[S_51].token = TK_NOTOKEN;
    states[S_54].token = TK_NOTOKEN;
    // states[S_60].token = TK_NOTOKEN;// possible error

    states[S_1].token = TK_SQL;
    states[S_2].token = TK_SQR;
    states[S_3].token = TK_COMMA;
    states[S_4].token = TK_SEM;
    states[S_5].token = TK_COLON;
    states[S_6].token = TK_DOT;
    states[S_7].token = TK_OP;
    states[S_8].token = TK_CL;
    states[S_9].token = TK_PLUS;
    states[S_10].token = TK_MINUS;
    states[S_11].token = TK_MUL;
    states[S_12].token = TK_DIV;
    states[S_15].token = TK_AND;
    states[S_18].token = TK_OR;
    states[S_19].token = TK_NOT;
    states[S_21].token = TK_EQ;
    states[S_23].token = TK_NE;

    states[S_25].token = TK_GE;
    states[S_26].token = TK_GT;
    states[S_28].token = TK_LE;
    states[S_31].token = TK_ASSIGNOP;
    states[S_32].token = TK_LT;
    states[S_33].token = TK_LT;

    states[S_36].token = TK_RUID;
    states[S_38].token = TK_NUM;
    states[S_40].token = TK_NUM;
    states[S_43].token = TK_RNUM;
    states[S_47].token = TK_RNUM;
    states[S_57].token = TK_ID;

    states[S_26].retract_count = 1;
    states[S_32].retract_count = 1;
    states[S_33].retract_count = 2;

    states[S_36].retract_count = 1;
    states[S_40].retract_count = 2;
    states[S_43].retract_count = 1;

    states[S_51].retract_count = 1;
    states[S_54].retract_count = 1;
    states[S_57].retract_count = 1;
    states[S_58].retract_count = 1;

    states[INVALID].retract_count = 1;
}

// Initializes the transitions of the DFA
void initialize_transitions()
{
    add_transition(START, (transition[]){f('%', S_59), f(' ', S_61), f('\n', S_62), f('~', S_19), f('[', S_1), f(']', S_2), f(',', S_3), f(';', S_4), f(':', S_5), f('.', S_6), f('(', S_7), f(')', S_8), f('=', S_20), f('+', S_9), f('-', S_10), f('!', S_22), f('@', S_16), f('&', S_13), f('#', S_34), f('*', S_11), f('>', S_24), f('<', S_27), f('/', S_12), f('_', S_48), f('\t', S_61)}, 25);
    // EQ AND NE
    add_transition(S_20, (transition[]){f('=', S_21)}, 1);
    add_transition(S_22, (transition[]){f('=', S_23)}, 1);

    //OR, AND
    add_transition(S_16, (transition[]){f('@', S_17)}, 1);
    add_transition(S_17, (transition[]){f('@', S_18)}, 1);
    add_transition(S_13, (transition[]){f('&', S_14)}, 1);
    add_transition(S_14, (transition[]){f('&', S_15)}, 1);

    // RUID
    add_transition(S_34, aToZ(S_35), 26);
    add_transition(S_35, aToZ(S_35), 26);
    theta(S_35, S_36);

    // COMMENT
    add_transition(S_59, (transition[]){f('\n', S_60)}, 1);
    theta(S_59, S_59);

    // comparison operators
    add_transition(S_24, (transition[]){f('=', S_25)}, 1);
    theta(S_24, S_26);
    add_transition(S_27, (transition[]){f('=', S_28), f('-', S_29)}, 2);
    theta(S_27, S_32);
    add_transition(S_29, (transition[]){f('-', S_30)}, 1);
    theta(S_29, S_33);
    add_transition(S_30, (transition[]){f('-', S_31)}, 1);

    //FUNID
    add_transition(S_48, AToZ(S_49), 52);
    add_transition(S_49, AToZ(S_49), 52);
    add_transition(S_49, zeroToNine(S_50), 10);
    theta(S_49, S_51);
    add_transition(S_50, zeroToNine(S_50), 10);
    theta(S_50, S_51);
    
    // ID
    add_transition(START, bToD(S_52), 3);
    add_transition(START, aToZExceptBToD(S_53), 23);
    add_transition(S_53, aToZ(S_53), 26);
    theta(S_53, S_54);
    add_transition(S_52, aToZ(S_53), 26);
    theta(S_52, S_58);
    add_transition(S_52, twoToSeven(S_55), 6);
    add_transition(S_55, bToD(S_55), 3);
    add_transition(S_55, twoToSeven(S_56), 6);
    theta(S_55, S_57);
    add_transition(S_56, twoToSeven(S_56), 6);
    theta(S_56, S_57);

    // NUM, RNUM
    add_transition(START, zeroToNine(S_37), 10);
    add_transition(S_37, zeroToNine(S_37), 10);
    add_transition(S_37, (transition[]){f('.', S_39)}, 1);
    theta(S_37, S_38);
    add_transition(S_39, zeroToNine(S_41), 10);
    theta(S_39, S_40);
    add_transition(S_41, zeroToNine(S_42), 10);
    add_transition(S_42, (transition[]){f('E', S_44)}, 1);
    theta(S_42, S_43);
    add_transition(S_44, (transition[]){f('+', S_45), f('-', S_45)}, 2);
    add_transition(S_44, zeroToNine(S_46), 10);
    add_transition(S_45, zeroToNine(S_46), 10);
    add_transition(S_46, zeroToNine(S_47), 10);
}

// Initializes the lookup table with the keywords and their respective tokens
void initialize_lookup_table()
{
    look_up_table = getTrieNode();
    insert(look_up_table, "with", TK_WITH);
    insert(look_up_table, "parameters", TK_PARAMETERS);
    insert(look_up_table, "end", TK_END);
    insert(look_up_table, "while", TK_WHILE);
    insert(look_up_table, "union", TK_UNION);
    insert(look_up_table, "endunion", TK_ENDUNION);
    insert(look_up_table, "definetype", TK_DEFINETYPE);
    insert(look_up_table, "as", TK_AS);
    insert(look_up_table, "type", TK_TYPE);
    insert(look_up_table, "_main", TK_MAIN);
    insert(look_up_table, "global", TK_GLOBAL);
    insert(look_up_table, "parameter", TK_PARAMETER);
    insert(look_up_table, "list", TK_LIST);
    insert(look_up_table, "input", TK_INPUT);
    insert(look_up_table, "output", TK_OUTPUT);
    insert(look_up_table, "int", TK_INT);
    insert(look_up_table, "real", TK_REAL);
    insert(look_up_table, "endwhile", TK_ENDWHILE);
    insert(look_up_table, "if", TK_IF);
    insert(look_up_table, "then", TK_THEN);
    insert(look_up_table, "endif", TK_ENDIF);
    insert(look_up_table, "read", TK_READ);
    insert(look_up_table, "write", TK_WRITE);
    insert(look_up_table, "return", TK_RETURN);
    insert(look_up_table, "call", TK_CALL);
    insert(look_up_table, "record", TK_RECORD);
    insert(look_up_table, "endrecord", TK_ENDRECORD);
    insert(look_up_table, "else", TK_ELSE);
}

// Returns the Lexical Token List of the file
vector getStream(FILE *fp)
{
    if (fp == NULL)
    {
        printf("Error: File not found\n");
        exit(1);
    }
    twinBuffer buffer = (twinBuffer)malloc(sizeof(struct TwinBuffer));
    buffer->secondary_buffer_index = 0;
    buffer->line_count = 1;
    FILE *new_fp = fopen("lexical_tokens.salad", "w");
    if (new_fp == NULL)
    {
        printf("Error: Could not create a new file\n");
        exit(1);
    }
    fprintf(new_fp, "%-30s %-30s %s\n", "Line", "Lexeme", "Token");
    fprintf(new_fp, "%-30s %-30s %s\n", "----", "------", "-----");

    vector v = init_vector();
    while (fgets(buffer->primary_buffer, MAX_BUFFER_SIZE, fp) != NULL)
    {
        tokenInfo info = getNextToken(buffer);
        for (int i = 0; i < info->token_count; i++)
        {
            push_back(v, info->tokens[i]);
            fprintf(new_fp, "%-30d %-30s %s\n", info->tokens[i]->lc, info->tokens[i]->lexeme, TOKENS[info->tokens[i]->tk]);
        }
        free(info);
    }
    fclose(fp);
    fclose(new_fp);
    free(buffer);
    return v;
}

// Returns the list of next tokens from the twin-buffer
tokenInfo getNextToken(twinBuffer buffer)
{
    state curr_state = &states[START];
    state prev_state = NULL;
    buffer->primary_buffer_index = 0;

    tokenInfo tokens = (tokenInfo)malloc(sizeof(TokenInfo));
    tokens->tokens = (token *)malloc(MAX_BUFFER_SIZE * sizeof(token));
    tokens->token_count = 0;

    char *keyword = (char *)malloc(100 * sizeof(char));

    char invalid_token[30];

    int till = 0;

    int is_filled = buffer->secondary_buffer_index > 0;

    int token_len = 0;
    int token_count = 0;
    int next = 1;
    int err_type = 0;

    while (till < buffer->secondary_buffer_index)
    {

        curr_state = get_next_state(curr_state, buffer->secondary_buffer[till]);
        token_len++;
        if (buffer->secondary_buffer[till] == '\n' && curr_state->retract_count == 0)
        {
            buffer->line_count++;
        }
        if (curr_state->token == S_51 && token_len > 30)
        {
            err_type = 3;
            curr_state = &states[INVALID];
        }
        else if (curr_state->token == TK_ID && token_len > 20)
        {
            err_type = 4;
            curr_state = &states[INVALID];
        }
        if (curr_state->token == TK_INVALID)
        {
            int next = (token_len == 1);
            till -= curr_state->retract_count;
            token_len -= curr_state->retract_count;
            memset(keyword, '\0', 100);
            memset(invalid_token, '\0', 30);
            if (err_type == 3)
            {
                strncpy(keyword, "Function Length Error", 22);
            }
            else if (err_type == 4)
            {
                strncpy(keyword, "Variable Length Error", 22);
            }
            else if (next)
            {
                strncpy(invalid_token, buffer->secondary_buffer + till - token_len + 1, token_len + next);
                sprintf(keyword, "Unknown Symbol <%s>", invalid_token);
            }
            else
            {
                strncpy(invalid_token, buffer->secondary_buffer + till - token_len + 1, token_len + next);
                if (token_len == 1)
                {
                    sprintf(keyword, "Unknown Symbol <%s>", invalid_token);
                }
                else
                {
                    sprintf(keyword, "Unknown Pattern <%s>", invalid_token);
                }
            }
            tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
            tokens->token_count++;
            token_len = 0;
            curr_state = &states[START];
            continue;
        }
        till -= curr_state->retract_count;
        token_len -= curr_state->retract_count;
        if (curr_state->token != -1)
        {
            // If the token is a comment, override lexeme and adjust line count.
            if (curr_state->state_id == S_60) {
                tokens->tokens[tokens->token_count] = 
                    getNewToken(curr_state->token, buffer->line_count - 1, "%");
                tokens->token_count++;
            }
            else {
                int len = token_len;
                if(curr_state->state_id == S_1 && len > 0 && buffer->secondary_buffer[till] == '\n')
                    len--;
                memset(keyword, '\0', 100);
                strncpy(keyword, buffer->secondary_buffer + till - token_len + 1, len);
                if (curr_state->state_id == S_51 || curr_state->state_id == S_53)
                {
                    token_id tk = search(look_up_table, keyword);
                    if (tk == TK_INVALID)
                    {
                        if (keyword[0] == '_')
                        {
                            tk = TK_FUNID;
                        }
                        else
                        {
                            tk = TK_FIELDID;
                        }
                    }
                    tokens->tokens[tokens->token_count] = getNewToken(tk, buffer->line_count, keyword);
                    tokens->token_count++;
                }
                if (curr_state->token != TK_NOTOKEN)
                {
                    tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
                    tokens->token_count++;
                }
            }
            curr_state = &states[START];
            token_len = 0;
        }
        till++;
        prev_state = curr_state;
    }
    // read from primary buffer
    while (buffer->primary_buffer_index < MAX_BUFFER_SIZE && buffer->primary_buffer[buffer->primary_buffer_index] != '\0')
    {

        curr_state = get_next_state(curr_state, buffer->primary_buffer[buffer->primary_buffer_index]);
        token_len++;
        if (buffer->primary_buffer[buffer->primary_buffer_index] == '\n' && curr_state->retract_count == 0)
        {
            buffer->line_count++;
        }
        if (curr_state->token == S_43 && token_len > 30)
        {

            err_type = 3;
            curr_state = &states[INVALID];
        }
        else if (curr_state->token == TK_ID && token_len > 20)
        {
            err_type = 4;
            curr_state = &states[INVALID];
        }
        if (curr_state->token == TK_INVALID)
        {
            int next = (token_len == 1);
            buffer->primary_buffer_index -= curr_state->retract_count;
            token_len -= curr_state->retract_count;
            memset(keyword, '\0', 100);
            memset(invalid_token, '\0', 30);
            if (err_type == 3)
            {
                strncpy(keyword, "Function Length Error", 22);
            }
            else if (err_type == 4)
            {
                strncpy(keyword, "Variable Length Error", 22);
            }
            else if (next)
            {
                strncpy(invalid_token, buffer->primary_buffer + buffer->primary_buffer_index - token_len + 1, token_len + next);
                sprintf(keyword, "Unknown Symbol <%s>", invalid_token);
            }
            else
            {
                strncpy(invalid_token, buffer->primary_buffer + buffer->primary_buffer_index - token_len + 1, token_len + next);
                if (token_len == 1)
                {
                    sprintf(keyword, "Unknown Symbol <%s>", invalid_token);
                }
                else
                {
                    sprintf(keyword, "Unknown Pattern <%s>", invalid_token);
                }
            }
            tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
            tokens->token_count++;
            buffer->primary_buffer_index++;
            buffer->primary_buffer_index += next;
            err_type = 0;
            token_len = 0;
            curr_state = &states[START];
            continue;
        }
        // s -> 1 -> 2 -> 3
        buffer->primary_buffer_index -= curr_state->retract_count;
        token_len -= curr_state->retract_count;
        if (curr_state->token != -1)
        {
            if (curr_state->state_id == S_60) {
                tokens->tokens[tokens->token_count] =
                    getNewToken(curr_state->token, buffer->line_count - 1, "%");
                tokens->token_count++;
            }
            else {
                int len = token_len;
                if(curr_state->state_id == S_1 && len > 0 && buffer->primary_buffer[buffer->primary_buffer_index] == '\n')
                    len--;
                memset(keyword, '\0', 100);
                if (token_len > buffer->primary_buffer_index + 1)
                {
                    strncpy(keyword, buffer->secondary_buffer, token_len - buffer->primary_buffer_index - 1);
                    strncpy(keyword + token_len - buffer->primary_buffer_index - 1, buffer->primary_buffer, buffer->primary_buffer_index + 1);
                }
                else
                {
                    strncpy(keyword, buffer->primary_buffer + buffer->primary_buffer_index - token_len + 1, len);
                }
                if (curr_state->state_id == S_51 || curr_state->state_id == S_53)
                {
                    token_id tk = search(look_up_table, keyword);
                    if (tk == TK_INVALID)
                    {
                        if (keyword[0] == '_')
                        {
                            tk = TK_FUNID;
                        }
                        else
                        {
                            tk = TK_FIELDID;
                        }
                    }
                    tokens->tokens[tokens->token_count] = getNewToken(tk, buffer->line_count, keyword);
                    tokens->token_count++;
                }
                if (curr_state->token != TK_NOTOKEN)
                {
                    tokens->tokens[tokens->token_count] = getNewToken(curr_state->token, buffer->line_count, keyword);
                    tokens->token_count++;
                }
            }
            curr_state = &states[START];
            token_len = 0;
        }
        buffer->primary_buffer_index++;
    }

    if (is_filled)
    {
        memset(buffer->secondary_buffer, '\0', MAX_BUFFER_SIZE);
    }

    if (curr_state == &states[S_0])
    {
        strncpy(buffer->secondary_buffer, "%", 1);
        buffer->secondary_buffer_index = 1;
    }
    else if (curr_state != &states[START])
    {
        strncpy(buffer->secondary_buffer, buffer->primary_buffer + MAX_BUFFER_SIZE - 1 - token_len, token_len + (token_len == 0));
        buffer->secondary_buffer_index = token_len;
    }
    else
    {
        buffer->secondary_buffer_index = 0;
    }
    free(keyword);
    return tokens;
}

// Return Next State of the DFA given a Character
state get_next_state(state current_state, char next_char)
{
    bool flag = false;
    // this loop seems redundant i guess?
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (ALPHABETS[i] == next_char)
        {
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        return &states[INVALID];
    }
    for (int i = 0; i < current_state->length; i++)
    {
        if (current_state->transitions[i]->next_char == next_char)
        {
            return current_state->transitions[i]->next_state;
        }
    }
    return &states[INVALID];
}

// Removes the comments from the test-case file and puts remaining input
// into a clean file
void removeComments(char *testcaseFile, char *cleanFile)
{
    FILE *testcase_fp = fopen(testcaseFile, "r");
    FILE *clean_fp = fopen(cleanFile, "w");
    if (testcase_fp == NULL)
    {
        printf("Error: Test Case File not found\n");
        exit(1);
    }
    if (clean_fp == NULL)
    {
        printf("Error: Could not create a new file\n");
        exit(1);
    }

    char interm = fgetc(testcase_fp);

    int comment = 0;

    while (interm != EOF)
    {
        if (interm == '%')
        {
            comment = 1;
        }
        if (comment == 1)
        {
            if (interm == '\n')
            {
                comment = 0;
            }
        }
        else
        {
            fputc(interm, clean_fp);
        }
        interm = fgetc(testcase_fp);
    }

    fclose(testcase_fp);
    fclose(clean_fp);
}
