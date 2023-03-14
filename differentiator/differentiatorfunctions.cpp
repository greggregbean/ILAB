#include "differentiator.h"

//TREE METHODS:
tree::tree()
{
    head_ = new treeEl{};
    head_ -> left = nullptr;
    head_ -> right = nullptr;
}

void tree::textDump()
{
    printf("Text dump: ");
    recursiveDump(head_, head_);
    printf("\n\n");
}

void tree::graphDump(FILE* filep)
{
    printf("GraphDump: ");

    fprintf(filep, "digraph \n{\n");
    recursiveGraph(filep, head_);
    fprintf(filep, "}");

    printf("your graph in \"graph.dot\". \n");
}

void tree::reader(FILE* filep)
{
    printf("READER: \n");
    head_ = MainParse(filep);
    printf("\n");
}

void tree::differentiator()
{
    printf("+++DIFFERENTIATOR+++  \n");
    head_ = recursiveDif(head_);
    printf("---DIFFERENTIATOR---  \n");
    printf("\n");
}

//DUMP:
void recursiveGraph(FILE* filep, treeEl* node)
{
    fprintf(filep, "%d [shape=record, fillcolor = wheat1, style = filled, label = \" {", node); 
    fprintVal(filep, node);
    fprintf(filep, "| Type: %c", node -> type);
    fprintf(filep, " | Addr: %p | {Left: %p | Right: %p }}\" ] \n", (void*) node, (void*) node -> left, (void*) node -> right);
    
    if (node -> left != nullptr)
    {
        fprintf(filep, "%d -> %d [label = \" Left \"]; \n", node, node -> left); 
        recursiveGraph(filep, node -> left);
    }

    if (node -> right != nullptr)
    {
        fprintf(filep, "%d -> %d [label = \" Right \"]; \n", node, node -> right); 
        recursiveGraph(filep, node -> right);
    }
}

void recursiveDump(treeEl* node, treeEl* head)
{
    if((node -> type != NUM) && (node -> type != VAR) && (node != head))
        printf("(");
    
    if (node -> left != nullptr)
        recursiveDump(node -> left, head);
    
    printVal(node);

    if (node -> right != nullptr)
        recursiveDump(node -> right, head);

    if((node -> type != NUM) && (node -> type != VAR) && (node != head))
        printf(")");    
}

void nodeDump(treeEl* node)
{
    printf("Addr: %p, Left: %p, Right: %p, Type: %c, Value: ", (void*)node, (void*)node -> left, (void*)node -> right, node -> type);
    printVal(node);
    printf("\n");
}

void fprintVal(FILE* filep, treeEl* node)
{
    if(node -> type == NUM)
        fprintf(filep, "%lg", (node -> val).number);

    else
        fprintf(filep, "%c", (node -> val).varOrOper);
}

void printVal(treeEl* node)
{
    if(node -> type == NUM)
        printf("%lg", (node -> val).number);

    else
        printf("%c", (node -> val).varOrOper);
}

//НАДО ДОРАБОТАТЬ
/*void AddDivDump(treeEl* node)
{
    if(node -> left != nullptr)
        MulSubDump(node -> left);

    printVal(node);

    if(node -> right != nullptr)
        MulSubDump(node -> right);
}

void MulSubDump(treeEl* node)
{
    if(node -> left != nullptr)
        PowDump(node -> left);

    printVal(node);

    if(node -> right != nullptr)
        PowDump(node -> right);
}

void PowDump(treeEl* node)
{
    if(node -> left != nullptr)
        VarNumDump(node -> left);

    printVal(node);

    if(node -> right != nullptr)
        VarNumDump(node -> right);
}

void VarNumDump(treeEl* node)
{
    if ((node -> type == NUM) || (node -> type == VAR))
        printVal(node);

    else
    {
        printf("(");
        AddDivDump(node);
        printf(")");
    }
}*/


//READER:
void spaceSkip(FILE* filep)
{
    char symbol;
    while(((symbol = getc(filep)) == ' ') || (symbol == '\t') || (symbol == '\r') || (symbol == '\n')) ;
    ungetc(symbol, filep);
}

treeEl* MainParse(FILE* filep)
{
    printf("Зашли в MainParse. \n");

    treeEl* mainNode = new treeEl{};

    mainNode = AddDivParse(filep);

    spaceSkip(filep);

    char symbol = getc(filep);
    printf("В MainParse считали %c. \n", symbol);

    if(symbol == '$')
        printf("Уравнение считано верно. \nВышли из MainParse.\n");

    else
        printf("Не обнаружен закрывающий символ '$'. \n");

    return mainNode;
}

treeEl* AddDivParse(FILE* filep)
{ 
    printf("Зашли в AddDivParse.\n");

    treeEl* addOrDiv = new treeEl{};

    addOrDiv -> left = MulSubParse(filep);

    spaceSkip(filep);

    char symbol = getc(filep);
    printf("В AddDivParse считали %c. \n", symbol);

    while(true)
    {
        if(symbol == ADD)
        {
            addOrDiv -> type = ADD;
            (addOrDiv -> val).varOrOper = ADD;
            addOrDiv -> right = AddDivParse(filep);

            nodeDump(addOrDiv);

            printf("Вышли из AddDivParse. \n");
            return addOrDiv;
        }

        else if(symbol == DIV)
        {
            addOrDiv -> type = DIV;
            (addOrDiv -> val).varOrOper = DIV;
            addOrDiv -> right = AddDivParse(filep);

            nodeDump(addOrDiv);

            printf("Вышли из AddDivParse. \n");
            return addOrDiv;
        }

        else
        {
            ungetc(symbol, filep);
            printf("Вышли из AddDivParse. \n");
            return addOrDiv -> left;
        }

        symbol = getc(filep);
        printf("В MulSub считали %c. \n", symbol);
    }

    addOrDiv -> right = MulSubParse(filep);
        
    nodeDump(addOrDiv);

    printf("Вышли из AddDivParse. \n");
    return addOrDiv;
}

treeEl* MulSubParse(FILE* filep)
{
    printf("Зашли в MulSubParse.\n");

    treeEl* mulOrSub = new treeEl{};

    mulOrSub -> left = PowParse(filep);

    spaceSkip(filep);

    char symbol = getc(filep);
    printf("В MulSub считали %c. \n", symbol);

    while (true)
    {
        if(symbol == MUL)
        {
            mulOrSub -> type = MUL;
            (mulOrSub -> val).varOrOper = MUL;
            mulOrSub -> right = MulSubParse(filep);

            nodeDump(mulOrSub);

            printf("Вышли из MulSubParse. \n");
            return mulOrSub;
        }

        else if(symbol == SUB)
        {
            mulOrSub -> type = SUB;
            (mulOrSub -> val).varOrOper = SUB;
            mulOrSub -> right = MulSubParse(filep);

            nodeDump(mulOrSub);

            printf("Вышли из MulSubParse. \n");
            return mulOrSub;
        }

        else
        {
            ungetc(symbol, filep);
            printf("Вышли из MulSubParse. \n");
            return mulOrSub -> left;
        }

        symbol = getc(filep);
        printf("В MulSub считали %c. \n", symbol);
    }

    mulOrSub -> right = PowParse(filep);

    nodeDump(mulOrSub);

    printf("Вышли из MulSubParse. \n");
    return mulOrSub;
}

treeEl* PowParse(FILE* filep)
{
    printf("Зашли в PowParse.\n");

    treeEl* pow = new treeEl{};

    pow -> left = VarNumParse(filep);
    
    spaceSkip(filep);

    char symbol = getc(filep);
    printf("В PowParse считали %c. \n", symbol);

    while(true)
    {
        if(symbol == POW)
        {
            pow -> type = POW;
            (pow -> val).varOrOper = POW;
            pow -> right = PowParse(filep);

            nodeDump(pow);

            printf("Вышли из PowParse. \n");
            return pow;   
        }

        else
        {
            ungetc(symbol, filep);
            printf("Вышли из PowParse. \n");
            return pow -> left;
        }

        symbol = getc(filep);
        printf("В MulSub считали %c. \n", symbol);
    }

    pow -> right = VarNumParse(filep);

    nodeDump(pow);

    printf("Вышли из PowParse. \n");
    return pow;
}

treeEl* VarNumParse(FILE* filep)
{
    printf("Зашли в VarNumParse.\n");

    spaceSkip(filep);

    char symbol = getc(filep);
    
    if((symbol <= '9') && (symbol >= '0'))
    {
        ungetc(symbol, filep);

        treeEl* num = new treeEl{};

        num -> type = NUM;
        fscanf(filep, "%lg", &((num -> val).number));
        num -> left  = nullptr;
        num -> right = nullptr;

        nodeDump(num);

        symbol = getc(filep);
        printf("Cчитали %lg, следующий символ \"%c\". \n", (num -> val).number, symbol);
        ungetc(symbol, filep); 

        printf("Вышли из VarNumParse. \n");
        
        return num;
    }

    else if ((symbol >= 'a') && (symbol <= 'z'))
    {
        treeEl* var = new treeEl{};

        var -> type = VAR;
        (var -> val).varOrOper = symbol;
        var -> left  = nullptr;
        var -> right = nullptr;

        nodeDump(var);

        symbol = getc(filep);
        printf("Cчитали %c, следующий символ \"%c\". \n", (var -> val).varOrOper, symbol);
        ungetc(symbol, filep);

        printf("Вышли из VarNumParse. \n");

        return var;
    }

    else if (symbol == '(')
    {
        treeEl* equation = AddDivParse(filep);
        if((symbol = getc(filep)) == ')')
        {
            printf("Считали выражение в скобках. \n");
            printf("Вышли из VarNumParse. \n");
            return equation;
        }
    }

    //else:
    ungetc(symbol, filep);
    printf("Вышли из VarNumParse. \n");
    return nullptr;    
}

//DIFFERENTIATOR:
treeEl* nodeToNum(treeEl* node, int num)
{
    free(node -> left);
    free(node -> right);
    node -> left = nullptr;
    node -> right = nullptr;

    (node -> val).number = num;
    node -> type = NUM;

    return node;
}

treeEl* newTreeEl(int type, value val, treeEl* left, treeEl* right)
{
    treeEl* node = new treeEl{};

    node -> left = left;
    node -> right = right;

    switch (type)
    {
        case NUM:
        {      
            node -> type = NUM;
            (node -> val).number = val.number;
            break;
        }

        case VAR:
        {
            node -> type = VAR;
            (node -> val).varOrOper = val.varOrOper;
            break;
        }

        case ADD:
        {
            node -> type = ADD;
            (node -> val).varOrOper = ADD;
            break;
        } 

        case DIV:
        {
            node -> type = DIV;
            (node -> val).varOrOper = DIV;
            break;
        }

        case POW:
        {
            node -> type = POW;
            (node -> val).varOrOper= POW;
            break;
        }

        case MUL:
        {
            node -> type = MUL;
            (node -> val).varOrOper = MUL;
            break;
        }

        case SUB:
        {
            node -> type = SUB;
            (node -> val).varOrOper = SUB;
            break;
        }
    }

    return node;
}

treeEl* recursiveCopy(treeEl* node)
{
    treeEl* newNode;

    if ((node -> left == nullptr) && (node -> right == nullptr))
    {
        newNode = newTreeEl(node -> type, node -> val, nullptr, nullptr);
    }

    else if (node -> left == nullptr)
    {
        newNode = newTreeEl(node -> type, node -> val, nullptr, recursiveCopy(node -> right));
    }

    else if (node -> right == nullptr)
    {
        newNode = newTreeEl(node -> type, node -> val, recursiveCopy(node -> left), nullptr);
    }

    else
    {
        newNode = newTreeEl(node -> type, node -> val, recursiveCopy(node -> left), recursiveCopy(node -> right));
    }

    return newNode;
}

treeEl* recursiveDif(treeEl* node)
{
    if (node -> type == NUM)
    {
        (node -> val).number = 0;
        printf("Продифференцировали число. \n");
        return node;
    }

    else if (node -> type == VAR)
    {
        (node -> val).number = 1;
        node -> type = NUM;
        printf("Продифференцировали переменную. \n");
        return node;
    }

    else if (node -> type == POW)
    {
        printf("Попали на степень. ");

        if ((node -> left -> type == NUM) && (node -> right -> type == NUM))
        {
            printf("Cлучай: NUM ^ NUM. \n");
            return nodeToNum(node, 0);
        }

        else if ((node -> left -> type == VAR) && (node -> right -> type == NUM))
        {
            printf("Случай: VAR ^ NUM. ");

            if((node -> right -> val).number == 0)
            {
                printf("Нулевая степень. \n");
                return nodeToNum(node, 0);
            }

            else if ((node -> right -> val).number == 1)
            {
                printf("Первая степень. \n");
                return nodeToNum(node, 1);
            }

            else
            {
                printf("Степень > 1. \n");

                value lowerPow;
                lowerPow.number = (node -> right -> val).number - 1;
                treeEl* powMinOne = newTreeEl(NUM, lowerPow, nullptr, nullptr);
                printf("- Создали ячейку с меньшей степенью. \n");

                value pow;
                pow.varOrOper = POW;
                treeEl* newPow = newTreeEl(POW, pow, node -> left, powMinOne);
                printf("- Создали новую ячейку со степенью. \n");
                
                node -> type = MUL;
                (node -> val).varOrOper = MUL;
                node -> left = newPow;
                printf("- Поменяли исходную ячейку степени на ячейку умножения. \n");

                return node;
            }                
        }

        else if (node -> right -> type == NUM)
        {
            printf("Случай: (...) ^ NUM. \n");

            if ((node -> right -> val).number == 0)
            {
                printf("Нулевая степень. \n");
                return nodeToNum(node, 0);
            }

            else if((node -> right -> val).number == 1)
            {
                printf("Первая степень. \n");
                free(node -> right);
                return recursiveDif(node -> left);
            }

            else
            {
                printf("Cтепень > 1. \n");

                value lowerPow;
                lowerPow.number = (node -> right -> val).number - 1;
                treeEl* powMinOne = newTreeEl(NUM, lowerPow, nullptr, nullptr);
                printf("- Создали ячейку с меньшей степенью. \n");

                value pow;
                pow.varOrOper = POW;
                treeEl* newPow = newTreeEl(POW, pow, recursiveCopy(node -> left), powMinOne);
                printf("- Создали новую ячейку со степенью. \n");

                value mul;
                mul.varOrOper = MUL;
                treeEl* newMul = newTreeEl(MUL, mul, newPow, recursiveDif(node -> left));
                printf("- Создали новую ячейку с умножением. \n");

                node -> type = MUL;
                (node -> val).varOrOper = MUL;
                node -> left = newMul;
                printf("- Поменяли исходную ячейку степени на ячейку умножения. \n");

                return node;
            }
        }

        else
        {
            printf("Случай: VAR ^ VAR. К сожалению, такое дифференциатор дифференцировать не умеет. :(\n");
            return nullptr;
        }
    }

    else if ((node -> type == ADD) || (node -> type == DIV))
    {
        printf("Попали на сложение или вычитание. ");

        if ((node -> left -> type == NUM) && (node -> right -> type == NUM))
        {
            printf("Случай: NUM +/- NUM. \n");
            return nodeToNum(node, 0);
        }

        else if (node -> left -> type == NUM)
        {
            printf("Случай: NUM +/- (...). \n");
            free(node -> left);
            node -> left = nullptr;
            return recursiveDif(node -> right);
        }

        else if (node -> right -> type == NUM)
        {
            printf("Случай: (...) +/- NUM. \n");
            free(node -> right);
            node -> right = nullptr;
            return recursiveDif(node -> left);
        }

        else
        {
            printf("Cлучай: (...) +/- (...). \n");
            node -> left = recursiveDif(node -> left);
            printf("- Продифференцировали первое слагаемое. \n");
            node -> right = recursiveDif(node -> right);
            printf("- Продифференцировали второе слагаемое. \n");
            return node;
        }
    }

    else if (node -> type == MUL)
    {
        printf("Попали на умножение. ");

        if ((node -> left -> type == NUM) && (node -> right -> type == NUM))
        {
            printf("Случай: NUM * NUM. \n");
            return nodeToNum(node, 0);
        }

        else if (node -> left -> type == NUM)
        {
            printf("Случай: NUM * (...). \n");

            if ((node -> left -> val).number == 0)
            {
                printf("Умножение на ноль. \n");
                return nodeToNum(node, 0);
            }

            else if ((node -> left -> val).number == 1)
            {
                printf("Умножение на 1. \n");
                free(node -> left);
                return recursiveDif(node -> right);
            } 

            else
            {
                node -> right = recursiveDif(node -> right);
                return node;
            }
        }

        else if (node -> right -> type == NUM)
        {
            printf("Случай: (...) * NUM. \n");

            if ((node -> right -> val).number == 0)
            {
                printf("Умножение на ноль. \n");
                return nodeToNum(node, 0);
            }

            else if ((node -> right -> val).number == 1)
            {
                printf("Умножение на 1. \n");
                free(node -> right);
                return recursiveDif(node -> left);
            }
            
            else
            {
                node -> left = recursiveDif(node -> left);
                return node;
            }
        }

        else
        {
            printf("Случай: (...) * (...). \n");

            value mul;
            mul.varOrOper = MUL;

            treeEl* oldRigthExp = recursiveCopy(node -> right);
            printf("- Сохранили копию правого поддерева.\n");

            treeEl* newMulLeft = newTreeEl(MUL, mul, recursiveCopy(node -> left), recursiveDif(node -> right));
            printf("- Создали левое произведение с исходным левым и продифференцированным правым поддеревами. \n");

            treeEl* newMulRight = newTreeEl(MUL, mul, recursiveDif(node -> left), oldRigthExp); 
            printf("- Создали правое произведение с продифференцированным левым поддеревом и копией правого. \n");

            node -> type = ADD;
            (node -> val).varOrOper = ADD;
            node -> left = newMulLeft;
            node -> right = newMulRight;
            printf("- Поменяли исходную ячейку умножения на ячейку суммы. \n");

            return node;
        }
    }

    else if (node -> type == SUB)
    {
        printf("Попали на деление. ");

        if (node -> left -> type == NUM && node -> right -> type == NUM)
        {
            printf("Случай: NUM / NUM. \n");
            return nodeToNum(node, 0);
        }

        else if(node -> left -> type == NUM)
        {
            printf("Случай: NUM / (...). \n");

            if ((node -> left -> val).number == 0)
            {
                printf("Деление 0 на (...). \n");
                return nodeToNum(node, 0);
            }

            else if ((node -> left -> val).number == 1)
            {
                printf("Деление 1 на (...). \n");

                node -> type = POW;
                (node -> val).varOrOper = POW;
                printf("- Заменили ячейку деления на ячейку сепени. \n");

                (node -> left -> val).number = -1;
                printf("- Поменяли значение левой ячейки на -1. \n");

                treeEl* oldLeft = node -> left;
                node -> left = node -> right;
                node -> right = oldLeft;
                printf("- Поменяли левою и правую ячейки местами. \n");

                return recursiveDif(node); 
            } 

            else
            {
                value negOne;
                negOne.number = -1;
                treeEl* negOneNode = newTreeEl(NUM, negOne, nullptr, nullptr);
                printf("- Создали ячейку '-1'. \n");

                value pow;
                pow.varOrOper = POW;
                treeEl* newPow = newTreeEl(POW, pow, node -> right, negOneNode);
                printf("- Cоздали ячейку степени. \n");

                node -> type = MUL;
                (node -> val).varOrOper = MUL;
                node -> right = recursiveDif(newPow);
                printf("- Поменяли ячейку деления на ячейку умножения. \n");

                return node;
            }
        }

        else if (node -> right -> type == NUM)
        {
            printf("Случай: (...)/NUM. \n");

            if ((node -> right -> val).number == 0)
            {
                printf("Ай-яй-яй на 0 делить нельзя. \n");
                return nullptr;
            }

            else if ((node -> right -> val).number == 1)
            {
                printf("Деление на 1. \n");

                free(node -> right);
                node -> right = nullptr;

                return recursiveDif(node -> left);
            }

            else
            {
                node -> left = recursiveDif(node -> left);
                return node;    
            }
        }

        else
        {
            printf("Случай: (...)/(...)");

            treeEl* leftCopy = recursiveCopy(node -> left);
            treeEl* rightCopy1 = recursiveCopy(node -> right);
            treeEl* rightCopy2 = recursiveCopy(node -> right);

            value mul;
            mul.varOrOper = MUL;
            treeEl* leftMul = newTreeEl(MUL, mul, recursiveDif(node -> left), rightCopy1);
            treeEl* rightMul = newTreeEl(MUL, mul, leftCopy, recursiveDif(node -> right));
            printf("- Создали две ячейки умножения в числителе. \n");

            value div;
            div.varOrOper = DIV;
            treeEl* divNode = newTreeEl(DIV, div, leftMul, rightMul);
            printf("- Создали ячеку вычитания в числителе. \n");

            value num;
            num.number = 2;
            treeEl* numNode = newTreeEl(NUM, num, nullptr, nullptr);
            printf("- Создали ячеку c числом 2. \n");

            value pow;
            pow.varOrOper = POW;
            treeEl* powNode = newTreeEl(POW, pow, rightCopy2, numNode);
            printf("- Создали ячейку степени в знаменателе. \n");

            node -> left = divNode;
            node -> right = powNode;
            printf("- Прикрепили ячейки деления и степени к ячейке деления. \n");

            return node;
        }
    }

    else
    {
        printf("!!!Differentiator doesn't know this function!!! \n");
        return nullptr;
    }
}


