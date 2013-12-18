import bb.cascades 1.2
import bb.system 1.2

Page {
    function checkValid (){
        var players = playerDropDown.selectedIndex + 5;
        var spies = spyDropDown.selectedIndex + 1;
        var blanks = whiteDropDown.selectedIndex + 1;
        console.log(players + " " + spies + " " + blanks);
        if(blanks + spies >= players/2){
            settingsMainPageToast.show();
        }
    }
    
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

        Label {
            text: "游戏设置"
            textStyle.fontStyle: FontStyle.Default
            textStyle.fontSize: FontSize.Large
        }
        Divider {
        }

        ScrollView {
            Container {
                topPadding: 20
                leftPadding: 50
                rightPadding: 50
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }

                DropDown {
                    id: playerDropDown
                    objectName: "playerDropDownQML"
                    onSelectedIndexChanged: {
                        checkValid ();
                    }
                    options: [
                        Option {
                            text: "5"
                            value: 5
                            selected: true
                        },
                        Option {
                            text: "6"
                            value: 6
                        },
                        Option {
                            text: "7"
                            value: 7
                        },
                        Option {
                            text: "8"
                            value: 8
                        },
                        Option {
                            text: "9"
                            value: 9
                        },
                        Option {
                            text: "10"
                            value: 10
                        },
                        Option {
                            text: "11"
                            value: 11
                        },
                        Option {
                            text: "12"
                            value: 12
                        },
                        Option {
                            text: "13"
                            value: 13
                        },
                        Option {
                            text: "14"
                            value: 14
                        }
                    ]
                    title: "玩家个数:"
                }
                
                DropDown {
                    id: spyDropDown
                    objectName: "spyDropDownQML"
                    onSelectedIndexChanged: {
                        checkValid ();
                    }
                    options: [
                        Option {
                            text: "1"
                            value: 1
                            selected: true
                        },
                        Option {
                            text: "2"
                            value: 2
                        }
                    ]
                    title: "卧底个数:"
                }
                
                DropDown {
                    id: whiteDropDown
                    objectName: "whiteDropDownQML"
                    onSelectedIndexChanged: {
                        checkValid ();
                    }
                    options: [
                        Option {
                            text: "1"
                            value: 1
                            selected: true
                        },
                        Option {
                            text: "2"
                            value: 2
                        }
                    ]
                    title: "白板个数:"
                }
                
                Divider {
                    
                }
                
                Button {
                    horizontalAlignment: HorizontalAlignment.Center
                    text: "设置名字"
                    onClicked: {
                        _App.setNameListView();
                        settingNAV.push(settingNamePage);
                    }
                }
                
                Divider {
                    
                }
                
                Label {
                    horizontalAlignment: HorizontalAlignment.Center
                    text: "Thanks for downloading this APP!
                    
https://github.com/b59wang/Spy-BB10 "  
                    multiline: true
                }
            }
        }
    }
    attachedObjects: [
        SystemToast {
            id: settingsMainPageToast
            body:"这样的设置大丈夫?"
        }
    ]
}
