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

            }

            Divider {

            }

            ScrollView {
                horizontalAlignment: HorizontalAlignment.Fill

                Container {
                    horizontalAlignment: HorizontalAlignment.Fill

                    ImageButton {
                        enabled: true
                        horizontalAlignment: HorizontalAlignment.Center
                        preferredHeight: 300
                        defaultImageSource: "asset:///images/button.png"
                    }
                    
                    Divider {
                    
                    }
                    
                    Label {
                        horizontalAlignment: HorizontalAlignment.Center
                        multiline: true
                        text: "游戏规则 : 
                            
1、每轮每个玩家只允许说一句话描述自己的身份词，既不能让卧底发现，也要给同伴暗示 4 x)

2、玩家发言完毕后开始投票，得票最多的玩家出局。

3、平民人数小于初始卧底人数时，卧底胜；卧底全部出局，平民胜 ."
                        textStyle.fontSize: FontSize.Medium
                    }
                }
            }
        }
    }
}
