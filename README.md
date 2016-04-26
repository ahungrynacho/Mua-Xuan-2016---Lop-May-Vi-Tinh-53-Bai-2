# Mua-Xuan-2016---Lop-May-Vi-Tinh-53-Bai-2

//Removes \n
        if ((strlen(line)>0) && (line[strlen(line) - 1] == '\n'))
            line[strlen(line) - 1] = '\0';
            
if (strstr(line, "quit") != NULL || strstr(line, "quit ") != NULL || strstr(line, "quit\t") != NULL ||
            strstr(line, " quit") != NULL || strstr(line, "\tquit") != NULL)
