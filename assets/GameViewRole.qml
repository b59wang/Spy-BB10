import bb.cascades 1.2
import bb.system 1.2

Page {
    actions: [
        ActionItem {
            id: action1
            title: "开始游戏！"
            imageSource: "asset:///images/icons/start.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                console.log("start game");
                _App.elimateSetup();
                gamePlayPage.win = false ;
                gameNAV.push(gamePlayPage);
            }
        }
    ]

    property string pickedWord

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
                    text: "玩家角色"
                    textStyle.fontStyle: FontStyle.Default
                    textStyle.fontSize: FontSize.Large
                }
                Label {
                    translationY: 20
                    text: "(请点击观看角色)"
                    textStyle.fontStyle: FontStyle.Default
                    textStyle.fontSize: FontSize.XXSmall
                }
            }

            Divider {

            }

            ListView {
                id: nameListView
                objectName: "gameRoleListViewQML"
                dataModel: ArrayDataModel {
                    id: theDataModel
                }

                listItemComponents: [
                    ListItemComponent {
                        StandardListItem {
                            title: ListItemData.name
                            // description: ListItemData.role
                            // status: ListItemData.word
                            imageSource: "asset:///images/spy.png"
                        }
                    }
                ]

                attachedObjects: [
                    SystemDialog {
                        id: prompt
                        title: "你的词语是: " + pickedWord
                        onFinished: {
                            if (result == SystemUiResult.ConfirmButtonSelection) {

                            }
                        }
                    }
                ]

                onTriggered: {
                    console.debug("Debug: clicked on " + dataModel.data(indexPath).name);
                    pickedWord = dataModel.data(indexPath).word;
                    prompt.show();
                }
            }
        }
    }
}
