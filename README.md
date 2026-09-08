# Intel 8086 Interpreter 

This intel 8086 interpreter is a g++ executable capable of interpreting intel 8086 architecture compiled files, using an emulated CPU.

It is a second version of a previous academic project.
The goal was to enhance readability, code maintenance, error handling and architecture,
while keeping the old functionalities and optimizing the program (using c++).

The disassembler was also fused with this project, usable through another flag's usage.

## Installation 

### Dependencies

This project uses :
- CMAKE
- g++

### Manual Installation

Once the source code is installed, in the root folder of the repository, you can run the command :
```shell
cmake -S . -B build/
```

This will create a `build` folder, where all compilation items will be placed.
Once the command finished, run the following:
```shell
cmake --build build/
```

This will create the executable file, in the `build` folder.

It will call `intel8084Interpreter`.

So the relative path from the root folder would ordinarily be `build/intel8084Interpreter`.

## Execution

This executable takes in an intel 8086 compiled executable (not runnable with current linux or windows interpreter).

### Interpreting

Using the following command in the root folder : 

```shell
./build/intel8084Interpreter <filepath>
```

will interpret the given file, using the emulated CPU.

The flag `-m` can be used to display all instruction actions on the CPU and the memory of the emulated system.

### Disassembling

Using the following command in the root folder : 
```shell
./build/intel8084Interpreter -d <filepath>
```

will disassemble the given file, showing all the instructions the executable can find.

> **Important**: The disassembling is done without caring about instruction execution. So the Control Transfer Instructions
will not impact the disassembling (ex: jmp instruction will not jump to another instruction).

## Tests

The project is packaged with given intel 8086 compiled files, which can be used to test the project.

They can be found in the `tests` folder at the root of the repository.

## Completion

This project is not yet fully functional.

Some instructions, syscall and other behavior are not yet implemented.

Proper exceptions should be thrown, to detail which type of error it could cause.

## Credits

