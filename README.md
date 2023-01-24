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
