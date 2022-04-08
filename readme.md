# A very simple text file handler

Perform simple CRUD operations on text files.

Example:

```
Howdy, what would you like to do? Type a character and press enter:
		[c] Create a file
		[q] Quit
c

Type the file name:
MyTestFile1

To add content, type whatever you want, and press enter to save and continue.
To stop, type exit and press enter.

----- Editing file MyTestFile1.txt -----
Lorem ipsum
dolor sit
amet
consectetur adipiscing
elit
exit
----- End editing file -----

What would you like to do now? Type a character and press enter:
		[c] Create a file
		[r] Read a file
		[u] Update a file
		[d] Delete a file
		[q] Quit
r

Which file would you like to read? Type a number and press enter:
		[1] /path/to/project/created-files/MyTestFile1.txt
1

----- Reading file MyTestFile1.txt -----
Lorem ipsum
dolor sit
amet
consectetur adipiscing
elit
----- End reading file -----

What would you like to do now? Type a character and press enter:
		[c] Create a file
		[r] Read a file
		[u] Update a file
		[d] Delete a file
		[q] Quit
d

Which file would you like to delete? Type a number and press enter:
		[1] /path/to/project/created-files/MyTestFile1.txt
1

----- Deleting file MyTestFile1.txt -----
----- End deleting file -----

What would you like to do now? Type a character and press enter:
		[c] Create a file
		[q] Quit
q
Catch ya later buddy!
```

Built to learn the basis of the C++ language.

# TODO

- Create and delete directory
- Change working directory
- Update file's at specific position
- Implement an object-oriented version