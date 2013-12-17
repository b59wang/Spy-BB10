import bb.cascades 1.2

/*
 * This is the overview tab page. The user sees this page first
 */
NavigationPane {
    id: gameNAV
    
    onCreationCompleted: {
        gameNAV.push(gameMainPage);
    }
    
    attachedObjects: [
        GameMainPage {
            id: gameMainPage
        } 
    ]

}
