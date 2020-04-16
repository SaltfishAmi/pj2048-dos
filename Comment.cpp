/*
--------------------------------------------------------------------------------
 KNOWN ISSUES:

 1) Screen misfunction when grid columns is more than lines;
 2) DOWN and RIGHT misfunctions;

--------------------------------------------------------------------------------

 TEMPORARY SOLUTIONS:

 1) Force the grid to be a square in which columns equal to lines;

--------------------------------------------------------------------------------

 TO-DO LIST:

 Priority Descending
 + Press P to toggle "[x] Prompt on overwriting"
    Completed but not tested
 + Write a universal Save/Load interface function  ==>
 + Difficulty enhancement(increase new2 generate rate at corners)
 * Fix Issue 2);
 * Permanently fix Issue 1);
 + Customize outputs from file;
 + Add background music and sound effects.

--------------------------------------------------------------------------------

 CHANGE LOGS:

  Symbols:

  _ = Foundation
  + = Addition
  - = Removal
  * = Revision/Modification
  / = Changes causing no effect in program

  0.0.0

 _ Grid painting
 _ Number generating

  0.0.1

 _ Moving

  1.0.0

 _ Adding (core completed)

  1.0.1

 * Bugfixes in Moving and Adding

  1.0.2

 - Removed 2x2 grid
 * Temporary bugfixes in gameplay

  1.0.3, 1.0.4

 * Bugfixes in number generating

  1.1.0

 + Added saving and loading function

  1.2.0

 + Added function of saving to and loading from files

  1.2.1, 1.2.2

 * Bugfixes in file operations

  1.2.5

 / Changed company name
 + Undo function (only undo once)

  1.2.6

 / Slight changes on code arrangement

  1.2.7

 * Moved Score and Round info rightward
 + Saveslot and filesave indicator
 * Clearing savedata after every restart
 / Big changes on source arrangement
 * Changed extension name of save files
 * Changed some visual elements

  1.2.8

 + Saving grid size to file

  1.2.9

 / Slight bugfixes in data assignment

  1.2.10, 1.2.11

 + Prompt on overwriting save slots and files
 + Function of skipping checking files existence

  1.2.12

 / Optimized program icon

  1.2.13

 / Functionization

--------------------------------------------------------------------------------
Save/Load interface
    Saving
        Normal saving (1, 2, 3)
            Perserving last overwritten save data
            Saving to file (1, 2, 3)
          //Saving as a protected save (cannot be deleted in 2048 save file management)
        ////Saving as a PIN protected save
    Loading
        Loading from normal save slots (1, 2, 3)
            Loading last overwritten save data
        Loading from file (1, 2, 3)
        \/**These files can be
            Perserved,
            Modified,
            Copied,
            Renamed,
            Replaced,
            Distributed manually. *\/
    Save data management
        Save data deleting
            Deleting normal save slots (1, 2, 3, Last Overwritten)
                One by one
                All at once
            Deleting save files (1, 2, 3)
          //*Except protected and PINned ones
                One by one
                All at once
            Deleting all normal and file saves at once
        Copying save data
        //*Except protected and PINned ones
            Copying normal save slots (1, 2, 3)
                *Treat this as an Overwritting too!!
            Copying save files (1, 2 ,3)
  //Advanced feature
  //    Protecting unprotected save file
  //    Deprotecting protected save file
////    Operations requires to specify a save file and enter its PIN
////        Changing PIN
////        DePINning
////        Deleting
    Disable/Reenable SL feature (this will set noSL=1)
//------------------------------------------------------------------------------
*/
