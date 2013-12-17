import bb.cascades 1.2

/*
 * This is the overview tab page. The user sees this page first
 */
NavigationPane {
    id: settingNAV
    
    onCreationCompleted: {
        settingNAV.push(settingMainPage);
    }
    
    attachedObjects: [
       SettingMainPage {
           id: settingMainPage
       },
       SettingNames {
           id: settingNamePage
       }
    ]

}
