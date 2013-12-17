import bb.cascades 1.2

Page {
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
                
                onCreationCompleted: {
                    theDataModel.append({
                            "name": "asdf",
                            "asd" : "asd"
                    });
                }
                
                listItemComponents: [
                    ListItemComponent {
                        StandardListItem {
                            title:  ListItemData.name
                            imageSource: "asset:///images/spy.png"
                        }
                    }
                ]
            }
        }
    }
}