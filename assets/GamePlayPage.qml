import bb.cascades 1.2
import bb.system 1.2

Page {
    actions: [
        ActionItem {
            id: action1
            title: "exit"
            imageSource: "asset:///images/icons/exit.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                gameNAV.navigateTo(gameMainPage);
            }
        }
    ]

    property string pickedWord
    property int pickedIndex
    property bool win : false

    Container {
        Container {
            leftPadding: 50
            rightPadding: 50
            layout: StackLayout {

            }
            //banner
            ImageView {
                id: imageBanner
                imageSource: "asset:///images/banner.png"
                horizontalAlignment: HorizontalAlignment.Fill
                preferredHeight: 160
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                Label {
                    text: "淘汰"
                    textStyle.fontStyle: FontStyle.Default
                    textStyle.fontSize: FontSize.Large
                }
                Label {
                    translationY: 20
                    text: "(点击角色=淘汰)"
                    textStyle.fontStyle: FontStyle.Default
                    textStyle.fontSize: FontSize.XXSmall
                }
            }

            Divider {

            }

            ListView {
                id: nameListView
                objectName: "gameListViewQML"
                dataModel: ArrayDataModel {
                    id: theDataModel
                }

                listItemComponents: [
                    ListItemComponent {
                        StandardListItem {
                            title: ListItemData.name
                            status: {
                                if (ListItemData.alive) {
                                    return "活着";
                                }
                                return "死亡";
                            }
                            description: ListItemData.role

                            imageSource: "asset:///images/spy.png"
                        }
                    }
                ]

                attachedObjects: [
                    SystemDialog {
                        id: prompt
                        title: qsTr("KILL " + pickedWord + "?")
                        onFinished: {
                            if (prompt.result == SystemUiResult.ConfirmButtonSelection) {
                                console.log("asd");
                                var my_result = _App.elimate(pickedIndex);
                                if (my_result != "") {
                                    winPrompt.body = my_result + "," + "是否想再来一句？";
                                    winPrompt.show();
                                    win = true;
                                }
                            }
                            console.log("asddd");
                        }
                    },
                    SystemDialog {
                        id: winPrompt
                        title: "Game Over"
                        onFinished: {
                            if (result == SystemUiResult.ConfirmButtonSelection) {
                                _App.gameSetup();
                                gameNAV.navigateTo(gameRolePage);
                            } else {
                              
                            }
                        }
                    }
                ]

                onTriggered: {
                    if(win){
                        return;
                    }
                    console.debug("Debug: clicked on " + dataModel.data(indexPath).name);
                    if (!dataModel.data(indexPath).alive){
                        return;
                    }
                    pickedWord = dataModel.data(indexPath).name;
                    pickedIndex = dataModel.data(indexPath).index;
                    prompt.show();
                }
            }
        }
    }
}
