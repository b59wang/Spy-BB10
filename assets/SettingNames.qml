import bb.cascades 1.2
import bb.system 1.2

Page {
    property int iIndex

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
                    text: "玩家名字"
                    textStyle.fontStyle: FontStyle.Default
                    textStyle.fontSize: FontSize.Large
                }
                Label {
                    translationY: 20
                    text: "(请点击更改名字)"
                    textStyle.fontStyle: FontStyle.Default
                    textStyle.fontSize: FontSize.XXSmall
                }
            }

            Divider {

            }

            ListView {
                id: nameListView
                objectName: "nameListViewQML"
                dataModel: ArrayDataModel {
                    id: theDataModel
                }

                listItemComponents: [
                    ListItemComponent {
                        StandardListItem {
                            title: ListItemData.name
                            imageSource: "asset:///images/spy.png"
                        }
                    }
                ]

                attachedObjects: [
                    SystemPrompt {
                        id: prompt
                        title: "Enter New Name"
                        onFinished: {
                            if (result == SystemUiResult.ConfirmButtonSelection) {
                                _App.changeName(iIndex, inputFieldTextEntry());
                            }
                        }
                    }
                ]

                onTriggered: {
                    console.debug("Debug: clicked on " + dataModel.data(indexPath).name);
                    iIndex = dataModel.data(indexPath).index;
                    prompt.show();

                }
            }
        }
    }
}