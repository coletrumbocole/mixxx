/**
* @file dlgprefcontroller.h
* @author Sean M. Pappalardo  spappalardo@mixxx.org
* @date Mon May 2 2011
* @brief Configuration dialog for a DJ controller
*/

#ifndef DLGPREFCONTROLLER_H_
#define DLGPREFCONTROLLER_H_

#include <QHash>

#include "controllers/controllerpreset.h"
#include "controllers/controllerpresetinfo.h"
#include "controllers/dlgcontrollerlearning.h"
#include "controllers/ui_dlgprefcontrollerdlg.h"
#include "configobject.h"
#include "preferences/dlgpreferencepage.h"

// Forward declarations
class Controller;
class ControllerManager;

class DlgPrefController : public DlgPreferencePage {
    Q_OBJECT
  public:
    DlgPrefController(QWidget *parent, Controller* controller,
                      ControllerManager* controllerManager,
                      ConfigObject<ConfigValue> *pConfig);
    virtual ~DlgPrefController();

  public slots:
    // Called when the OK button is pressed.
    void slotApply();
    // Called when the dialog is displayed.
    void slotUpdate();
    // Called when the user toggles the enabled checkbox.
    void slotEnableDevice(bool enable);
    // Called when the user selects a preset from the combobox.
    void slotLoadPreset(int index);
    // Mark that we need to apply the settings.
    void slotDirty ();
    // Reload the mappings in the dropdown dialog
    void enumeratePresets();

  signals:
    void controllerEnabled(DlgPrefController*, bool);
    void openController(Controller* pController);
    void closeController(Controller* pController);
    void loadPreset(Controller* pController, QString controllerName, bool force);
    void clearInputs();
    void clearOutputs();
    void mappingStarted();
    void mappingEnded();;

  private slots:
    void slotPresetLoaded(ControllerPresetPointer preset);
    void slotShowLearnDialog();

    // Input mappings
    void clearAllInputBindings();
    //void slotRemoveInputMapping() {};
    //void slotAddInputMapping() {};

    // Output mappings
    void clearAllOutputBindings();

  private:
    QString presetShortName(const ControllerPresetPointer pPreset) const;
    QString presetDescription(const ControllerPresetPointer pPreset) const;
    QString presetForumLink(const ControllerPresetPointer pPreset) const;
    QString presetWikiLink(const ControllerPresetPointer pPreset) const;
    void savePreset(QString path);

    void enableDevice();
    void disableDevice();

    Ui::DlgPrefControllerDlg m_ui;
    ConfigObject<ConfigValue>* m_pConfig;
    ControllerManager* m_pControllerManager;
    Controller* m_pController;
    DlgControllerLearning* m_pDlgControllerLearning;
    QSpacerItem* m_pVerticalSpacer;
    bool m_bDirty;
};

#endif /*DLGPREFCONTROLLER_H_*/