import bb.cascades 1.2

/*
 * This is the overview tab page. The user sees this page first
 */
NavigationPane {
    id: gameNAV

    onCreationCompleted: {
        gameNAV.push(gameMainPage);
    }

    onTopChanged: {
        if (page == gameRolePage || page == gamePlayPage) {
            gameNAV.backButtonsVisible = false;
        }
    }
    attachedObjects: [
        GameMainPage {
            id: gameMainPage
        },
        GameViewRole {
            id: gameRolePage
        },
        GamePlayPage {
            id: gamePlayPage
        }
    ]

}
