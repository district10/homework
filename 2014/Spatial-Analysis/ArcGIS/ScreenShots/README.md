截图说明
=======


* 这些图在七牛上备份有，方便我博客里引用
* 大概是 `aa_arcgis_logo.png` ===> `qiniu`
* 本地撰写报告的时候我用的这些图，发到简书上我用七牛的链接
    
    * 用脚本把报告了的链接改下就可以了，大概是这样(现在没网，图都没传）：
```
qiniu_prefix="qiniu"
for i in *.png;
do
	echo ${qiniu_prefix}/$i
done
```

    * 或者直接在 Emacs 里弄 `s/ScreenShots\/*.png/ooe.png/g` (evil-mode)
