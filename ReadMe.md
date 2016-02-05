# PatentCheck说明

本项目使用Qt来编写一个native界面程序，用来检索专利申请说明书中的附图标记不一致等文字错误。

将专利局代码化的说明书全文粘贴进程序的编辑框内，点击按钮即可进行分析。分析完成后，生成一个窗口来显示相关信息。

目前只想到了使用正则表达式匹配的方式来找出所有附图标记以及相应的段落，从而清晰地显示出各不一致的地方。相关功能正在实现中。

后续其他功能会根据审查员的想法做进一步的拓展。