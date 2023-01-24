# C-List
 My attempt in recreating C#'s generic list in C language with a program that let's you write different types of list.

Limitations:
1) The ListTypeWriter is unable to create pointer lists. The way to do so (using the typewriter) is for the pointer to be nested inside of a struct and create a struct list.
2) The ListTypeWriter is only able to create
   - Struct list
   - int list
   - float list
   - double list
   - long list
   - char list

3) Has not been rigorously tested for all kinds of input in the terminal when you run ListTypeWriter.c


How to use the type writer
1) Run ListTypeWriter.c in IDE or run ListTypeWriter.exe

2) Type in the path (including the filename that is to be created) of your new list to be created in. (If only filename is inputted, the file will be created in the same folder as the script)

3) Type in the definition of your list element. (Make sure to end your text with '`' before pressing enter)

4) Type in the default value of your list element. (Make sure to end your text with '`' before pressing enter)

5) Check your new file to see if there are any errors or code that the typewriter was unable to write for you.
