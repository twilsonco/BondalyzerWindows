#include "ADDGLBL.h"
#include "GUIDEFS.h"
#include "core/LoadData.h"

AddOn_pa AddOnID;

void STDCALL LoaderSelectedCallback(void)
{
    /*
     * This function is called when
     * the user selects this dataset
     * loader from the list of importers
     * in the File/Import dialog.
     *
     * TODO:
     *
     * 1. Launch a dialog which collects settings
     *    for how the file should be loaded.
     *    (filename, skip, etc.)
     *
     * 2. In the OK callback of the dialog, close the dialog
     *    and call a function to load the data using the
     *    indicated settings. Note: you may want to use
     *    the same function to load the data from the
     *    LoaderCallback() function above.
     *
     * 3. IMPORTANT: After the data has been successfully loaded,
     *    be sure to call TecUtilImportSetLoaderInstr(). This will allow
     *    the user to save a layout file which references this
     *    custom loader.
     */
    TecUtilLockStart(AddOnID);
    BuildDialog1(MAINDIALOGID);
    TecGUIDialogLaunch(Dialog1Manager);
    TecUtilLockFinish(AddOnID);
}

/**
 * This function is called when the
 * $!EXTENDEDCOMMAND macro command is
 * processed.
 */
static Boolean_t STDCALL MacroCommandCallback(char *MacroCommandString,  /* IN */
                                              char **ErrMsg)             /* OUT (only if returning FALSE) */
{

    Boolean_t IsOk = TRUE;

    /*
     * MacroCommandString is the add-on macro command string needing processing.
     *
     * *ErrMsg is an error message string which must be allocated and set by this
     * function if and only if the return value is FALSE.
     */

    TecUtilLockStart(AddOnID);

    /*
     * TODO: Process the macro command.
     *
     * Example:
     *
     * $!EXTENDEDCOMMAND COMMANDPROCESSORID='Load By Value' COMMAND='MYCOMMAND'
     */

    if (!strcmp(MacroCommandString, "MYCOMMAND")) /* For example */
    {
        /* IsOk = ProcessMacroCommand_MYCOMMAND(); */
    }

    if (!IsOk)
    {
        /*
         * Some kind of error, so inform the user about it.
         */

        *ErrMsg = TecUtilStringAlloc(1000, "String for Error Message");
        strcpy(*ErrMsg, "Error processing macro command");
    }
    else
    {
        /* Ignore the *ErrMsg parameter */
    }

    TecUtilLockFinish(AddOnID);
    return (IsOk);
}

/**
 */
static void STDCALL StateChangeCallback(StateChange_e StateChange)
{

    switch (StateChange)
    {
            /*
             * This function will be called by Tecplot
             * each time a state change occurs.
             *
             *
             * NOTE:
             *
             * Some State changes also have some supplemental "state"
             * information that can be retrieved if you desire.
             * Comments in the case statements below identify these
             * state changes.  To retrieve the supplemental information
             * use the functions TecUtilStateChangeGetXXXXX. You may
             * only call these functions during the scope of this
             * callback.  Once control returns from this call the
             * supplemental information will become unaccessible.
             *
             */

            /*   State Change                Supplemental information */

        case StateChange_VarsAltered:     /* set of altered variables */
        case StateChange_VarsAdded:       /* set of added variables */
        case StateChange_ZonesDeleted:    /* set of deleted zones */
        case StateChange_ZonesAdded:      /* set of added zones */
        case StateChange_NodeMapsAltered: /* set of node maps altered */
        case StateChange_MouseModeUpdate: /* the new mouse mode */
        case StateChange_Style:           /* Style Parameters P1,P2,P3,P4,P5,P6 */
        case StateChange_View:            /* View action (View_e) */
        case StateChange_Streamtrace:     /* Streamtrace action (Streamtrace_e) */
        case StateChange_AuxDataAltered:  /* Auxiliary Location (AuxDataLocation_e)*/
        case StateChange_AuxDataAdded:    /* Auxiliary Location (AuxDataLocation_e)*/
        case StateChange_AuxDataDeleted:  /* Auxiliary Location (AuxDataLocation_e)*/

            /* State changes which do not have any supplemental "state" information. */
        case StateChange_FrameDeleted:        /* A frame was delete */
        case StateChange_NewTopFrame:         /* A new frame has become the current frame */
        case StateChange_Text:                /* One or more text elements has changed */
        case StateChange_Geom:                /* One or more geometry elements has changed */
        case StateChange_DataSetReset:        /* A new dataset has been loaded */
        case StateChange_NewLayout:           /* The current layout has been cleared and reset */
        case StateChange_CompleteReset:       /* Anything could have happened */
        case StateChange_LineMapAssignment:   /* A line mapping definition has been altered (includes zone and axis information) */
        case StateChange_ContourLevels:       /* The contour levels have been altered */
        case StateChange_ModalDialogLaunch:   /* A modal dialog has been launched */
        case StateChange_ModalDialogDismiss:  /* A modal dialog has been dismissed */
        case StateChange_QuitTecplot:         /* Tecplot is about to exit */
        case StateChange_ZoneName:            /* The name of a zone has been altered */
        case StateChange_VarName:             /* The name of a variable has been altered */
        case StateChange_LineMapName:           /* The name of an X-Y mapping has been altered */
        case StateChange_LineMapAddDeleteOrReorder: /* The set of existing X-Y mappings has been altered */
        case StateChange_ColorMap:            /* The color mapping has been altered */
        case StateChange_ContourVar:          /* The contour variable has been reassigned */
        case StateChange_NewAxisVariables:    /* The axis variables have been reassigned */
        case StateChange_PickListCleared:     /* All picked objects are unpicked */
        case StateChange_PickListGroupSelect: /* A group of objects has been added to the pick list */
        case StateChange_PickListSingleSelect:/* A single object has been added to or removed from the pick list */
        case StateChange_PickListStyle:       /* An action has been performed on all of the objects in the pick list */
        case StateChange_DataSetFileName:     /* The current data set has been saved to a file */
        case StateChange_DataSetTitle:        /* The current data set title has been changed */
        case StateChange_DataSetLockOn:       /* The dataset attached to the active frome in Tecplot has been locked */
        case StateChange_DataSetLockOff:      /* The dataset attached to the active frome in Tecplot has been unlocked */
        case StateChange_DrawingInterrupted:  /* The user has interrupted the drawing */


            /* Version 9 and later Note: If you are using modeless dialogs, you should
               trap the following state changes and take appropriate
               action when print preview is launched and dismissed.

               Usually you will either disable or close your dialog
               when print preview is launched. */

        case StateChange_PrintPreviewLaunch:  /* Modeless dialogs should close or disable themselves */
        case StateChange_PrintPreviewDismiss: /* Modeless dialogs can re-launch or enable themselves */


        case StateChange_SuspendInterface:    /* Replaces StateChange_DrawGraphicsOn */
        case StateChange_UnsuspendInterface:  /* Replaces StateChange_DrawGraphicsOff */
        {
            /* TODO: Add code to handle state changes.... */
        } break;
        default: break;
    } /* end switch */
}


/**
 * When Tecplot first loads an add-on, it makes a
 * call to initialize the add-on. This function
 * must be named InitTecAddOn, as shown below.
 */
EXPORTFROMADDON void STDCALL InitTecAddOn(void)
{


    /*
     * NOTE:  TecUtilLockOn MUST be used for InitTecAddOn instead
     *        of TecUtilLockStart because AddonID has yet to be
     *        established.  TecUtilLockOn is in effect an "annonymous"
     *        locking of tecplot (old style).
     */

    TecUtilLockOn();

    /*
     * The function TecUtilAddOnRegister() is the
     * only function that is REQUIRED to be called from
     * the initialization function.
     *
     * The information you give Tecplot by calling
     * this function will show up in the Help/About Add-ons
     * dialog box.
     */

    /*
     * Note that if your add-on requires a specific version of Tecplot,
     * you would check for that here using TecUtilGetTecplotVersion()
     */

    AddOnID = TecUtilAddOnRegister(100,
                                   ADDON_NAME,
                                   "V"ADDON_VERSION" ("TecVersionId") "ADDON_DATE,
                                   "Tecplot, Inc.");

    /*
     * Initialize the Tecplot GUI Builder libraries.
     */
    InitTGB();

    TecUtilImportAddLoader(LoaderCallback,
                           LoaderName.c_str(),
                           LoaderSelectedCallback,
                           NULL);

    TecUtilMacroAddCommandCallback(ADDON_NAME,
                                   MacroCommandCallback);
    {
        ArgList_pa ArgList;
        ArgList = TecUtilArgListAlloc();
        TecUtilArgListAppendFunction(ArgList, SV_CALLBACKFUNCTION, (const void *)StateChangeCallback);
        TecUtilArgListAppendInt(ArgList,      SV_STATECHANGEMODE,  StateChangeMode_v100);
        TecUtilStateChangeAddCallbackX(ArgList);
        TecUtilArgListDealloc(&ArgList);
    }



    /*
     * See note on TecUtilLockOn at start of this function.
     */
    TecUtilLockOff();
}

