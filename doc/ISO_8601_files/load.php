var isCompatible=function(){if(navigator.appVersion.indexOf('MSIE')!==-1&&parseFloat(navigator.appVersion.split('MSIE')[1])<6){return false;}return true;};var startUp=function(){mediaWiki.loader.register([["site","1314134768",[],"site"],["startup","1315880878",[],"startup"],["user","1145459700",[],"user"],["user.options","1145459700",[],"private"],["filepage","1145459700",[]],["skins.vector",1307648762,[]],["skins.simple",1297545884,[]],["jquery",1297546087,[]],["jquery.async",1297546087,[]],["jquery.appear",1304959880,[]],["jquery.autoEllipsis",1297546087,["jquery.highlightText"]],["jquery.checkboxShiftClick",1297546087,[]],["jquery.client",1297417818,[]],["jquery.collapsibleTabs",1304454600,[]],["jquery.color",1297546087,[]],["jquery.cookie",1297546087,[]],["jquery.delayedBind",1297546087,[]],["jquery.expandableField",1297546087,[]],["jquery.highlightText",1315567972,[]],["jquery.placeholder",1300655278,[]],["jquery.json",1304003229,[]],["jquery.localize",1311631364,[]],[
"jquery.suggestions",1297546087,["jquery.autoEllipsis"]],["jquery.tabIndex",1297546087,[]],["jquery.textSelection",1300632620,[]],["jquery.tipsy",1300130330,[]],["jquery.ui.core",1297546096,["jquery"]],["jquery.ui.widget",1297546096,[]],["jquery.ui.mouse",1297546096,["jquery.ui.widget"]],["jquery.ui.position",1297546096,[]],["jquery.ui.draggable",1297546096,["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"]],["jquery.ui.droppable",1297546096,["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget","jquery.ui.draggable"]],["jquery.ui.resizable",1297546096,["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.selectable",1297546096,["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.sortable",1297546096,["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.accordion",1297546096,["jquery.ui.core","jquery.ui.widget"]],["jquery.ui.autocomplete",1297546096,["jquery.ui.core","jquery.ui.widget","jquery.ui.position"]],["jquery.ui.button",
1300130330,["jquery.ui.core","jquery.ui.widget"]],["jquery.ui.datepicker",1297546096,["jquery.ui.core"]],["jquery.ui.dialog",1297546096,["jquery.ui.core","jquery.ui.widget","jquery.ui.button","jquery.ui.draggable","jquery.ui.mouse","jquery.ui.position","jquery.ui.resizable"]],["jquery.ui.progressbar",1297546096,["jquery.ui.core","jquery.ui.widget"]],["jquery.ui.slider",1297546096,["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"]],["jquery.ui.tabs",1297546096,["jquery.ui.core","jquery.ui.widget"]],["jquery.effects.core",1297546097,["jquery"]],["jquery.effects.blind",1297546096,["jquery.effects.core"]],["jquery.effects.bounce",1297546097,["jquery.effects.core"]],["jquery.effects.clip",1297546097,["jquery.effects.core"]],["jquery.effects.drop",1297546097,["jquery.effects.core"]],["jquery.effects.explode",1297546097,["jquery.effects.core"]],["jquery.effects.fold",1297546097,["jquery.effects.core"]],["jquery.effects.highlight",1297546097,["jquery.effects.core"]],[
"jquery.effects.pulsate",1297546097,["jquery.effects.core"]],["jquery.effects.scale",1297546097,["jquery.effects.core"]],["jquery.effects.shake",1297546097,["jquery.effects.core"]],["jquery.effects.slide",1297546097,["jquery.effects.core"]],["jquery.effects.transfer",1297546097,["jquery.effects.core"]],["mediawiki",1315848487,[]],["mediawiki.util",1315424519,["jquery.checkboxShiftClick","jquery.client","jquery.placeholder"]],["mediawiki.Uri",1314636075,[]],["mediawiki.action.history",1297546088,["mediawiki.legacy.history"],"mediawiki.action.history"],["mediawiki.action.edit",1300126148,[]],["mediawiki.action.view.rightClickEdit",1297546088,[]],["mediawiki.special.preferences","1315880851",[]],["mediawiki.special.search",1297546088,[]],["mediawiki.language",1297546090,[]],["mediawiki.legacy.ajax","1315880814",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.ajaxwatch",1297545883,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.block",1297545883,["mediawiki.legacy.wikibits"]],[
"mediawiki.legacy.commonPrint",1310761761,[]],["mediawiki.legacy.config",1297545883,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.diff",1304454599,["mediawiki.legacy.wikibits"],"mediawiki.action.history"],["mediawiki.legacy.edit",1297545883,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.enhancedchanges",1297545883,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.history",1297545883,["mediawiki.legacy.wikibits"],"mediawiki.action.history"],["mediawiki.legacy.htmlform",1297545883,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.IEFixes",1297545883,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.metadata","1315880819",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.mwsuggest","1315880814",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.prefs",1297545883,["mediawiki.legacy.wikibits","mediawiki.legacy.htmlform"]],["mediawiki.legacy.preview",1297841696,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.protect",1297545883,["mediawiki.legacy.wikibits"]],[
"mediawiki.legacy.search",1300126148,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.shared",1315837643,[]],["mediawiki.legacy.oldshared",1297545883,[]],["mediawiki.legacy.upload",1297545883,["mediawiki.legacy.wikibits"]],["mediawiki.legacy.wikibits","1315880814",["mediawiki.language"]],["mediawiki.legacy.wikiprintable",1297545883,[]],["ext.gadget.Navigation_popups","1301011012",[]],["ext.gadget.Twinkle","1314963387",["mediawiki.util","jquery.ui.dialog","jquery.tipsy"]],["ext.gadget.HotCat","1301093212",[]],["ext.gadget.textareasansserif","1230150996",[]],["ext.gadget.purgetab","1309793310",["mediawiki.util"]],["ext.gadget.UTCLiveClock","1297883148",[]],["ext.gadget.dropdown-menus","1275306353",[]],["ext.gadget.NoSmallFonts","1299112018",[]],["ext.gadget.MenuToTabs","1309796148",[]],["ext.gadget.MenuTabsToggle","1314643264",[]],["ext.gadget.Blackskin","1304870533",[]],["ext.gadget.widensearch","1297966058",[]],["ext.gadget.DejaVu_Sans","1206084361",[]],["ext.articleFeedback.startup",
1309455062,["mediawiki.util"]],["ext.articleFeedback","1315880814",["jquery.ui.dialog","jquery.ui.button","jquery.articleFeedback","jquery.cookie","jquery.clickTracking"]],["ext.articleFeedback.dashboard",1304959880,[]],["jquery.articleFeedback","1315880814",["jquery.appear","jquery.tipsy","jquery.json","jquery.localize","jquery.ui.dialog","jquery.ui.button","jquery.cookie","jquery.clickTracking"]],["ext.wikihiero",1315426567,[]],["ext.checkUser",1297545985,["mediawiki.legacy.block"]],["ext.collection.jquery.json",1297545942,[]],["ext.collection.jquery.jstorage",1297545942,["ext.collection.jquery.json"]],["ext.collection.suggest",1297545942,["ext.collection.bookcreator"]],["ext.collection",1297545942,["ext.collection.bookcreator","jquery.ui.sortable"]],["ext.collection.bookcreator",1297545942,["ext.collection.jquery.jstorage"]],["ext.collection.checkLoadFromLocalStorage",1297545942,["ext.collection.jquery.jstorage"]],["ext.vector.collapsibleNav","1315880814",["jquery.client",
"jquery.cookie","jquery.tabIndex"],"ext.vector"],["ext.vector.collapsibleTabs",1309892768,["jquery.collapsibleTabs","jquery.delayedBind"],"ext.vector"],["ext.vector.editWarning","1315880814",[],"ext.vector"],["ext.vector.expandableSearch",1309892767,["jquery.client","jquery.expandableField","jquery.delayedBind"],"ext.vector"],["ext.vector.footerCleanup",1309892767,[],"ext.vector"],["ext.vector.sectionEditLinks",1300402032,["jquery.cookie","jquery.clickTracking"],"ext.vector"],["ext.vector.simpleSearch","1315880814",["jquery.client","jquery.suggestions","jquery.autoEllipsis","jquery.placeholder"],"ext.vector"],["contentCollector",1297545930,[],"ext.wikiEditor"],["jquery.wikiEditor","1315880819",["jquery.client","jquery.textSelection","jquery.delayedBind"],"ext.wikiEditor"],["jquery.wikiEditor.iframe",1297868152,["jquery.wikiEditor","contentCollector"],"ext.wikiEditor"],["jquery.wikiEditor.dialogs",1301840189,["jquery.wikiEditor","jquery.wikiEditor.toolbar","jquery.ui.dialog",
"jquery.ui.button","jquery.ui.draggable","jquery.ui.resizable","jquery.tabIndex"],"ext.wikiEditor"],["jquery.wikiEditor.highlight",1297545931,["jquery.wikiEditor","jquery.wikiEditor.iframe"],"ext.wikiEditor"],["jquery.wikiEditor.preview",1297545931,["jquery.wikiEditor"],"ext.wikiEditor"],["jquery.wikiEditor.previewDialog",1297545931,["jquery.wikiEditor","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.publish",1297545931,["jquery.wikiEditor","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.templateEditor",1297545930,["jquery.wikiEditor","jquery.wikiEditor.iframe","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.templates",1297545931,["jquery.wikiEditor","jquery.wikiEditor.iframe"],"ext.wikiEditor"],["jquery.wikiEditor.toc",1297545931,["jquery.wikiEditor","jquery.wikiEditor.iframe","jquery.ui.draggable","jquery.ui.resizable","jquery.autoEllipsis","jquery.color"],"ext.wikiEditor"],["jquery.wikiEditor.toolbar",1298232871,[
"jquery.wikiEditor"],"ext.wikiEditor"],["ext.wikiEditor",1297545931,["jquery.wikiEditor"],"ext.wikiEditor"],["ext.wikiEditor.dialogs",1297545931,["ext.wikiEditor","ext.wikiEditor.toolbar","jquery.wikiEditor.dialogs","jquery.suggestions"],"ext.wikiEditor"],["ext.wikiEditor.highlight",1297545930,["ext.wikiEditor","jquery.wikiEditor.highlight"],"ext.wikiEditor"],["ext.wikiEditor.preview",1297545931,["ext.wikiEditor","jquery.wikiEditor.preview"],"ext.wikiEditor"],["ext.wikiEditor.previewDialog",1297545930,["ext.wikiEditor","jquery.wikiEditor.previewDialog"],"ext.wikiEditor"],["ext.wikiEditor.publish",1297545931,["ext.wikiEditor","jquery.wikiEditor.publish"],"ext.wikiEditor"],["ext.wikiEditor.templateEditor",1297545931,["ext.wikiEditor","ext.wikiEditor.highlight","jquery.wikiEditor.templateEditor"],"ext.wikiEditor"],["ext.wikiEditor.templates",1297545931,["ext.wikiEditor","ext.wikiEditor.highlight","jquery.wikiEditor.templates"],"ext.wikiEditor"],["ext.wikiEditor.toc",1297545931,[
"ext.wikiEditor","ext.wikiEditor.highlight","jquery.wikiEditor.toc"],"ext.wikiEditor"],["ext.wikiEditor.tests.toolbar",1297545930,["ext.wikiEditor.toolbar"],"ext.wikiEditor"],["ext.wikiEditor.toolbar",1315424476,["ext.wikiEditor","ext.wikiEditor.toolbar.i18n","jquery.wikiEditor.toolbar","jquery.cookie","jquery.async"],"ext.wikiEditor"],["ext.wikiEditor.toolbar.i18n","1145459700",[],"ext.wikiEditor"],["ext.prefSwitch",1297546041,["jquery.client"]],["jquery.clickTracking",1303848806,["jquery.cookie"]],["ext.clickTracking",1300131238,["jquery.clickTracking"]],["ext.clickTracking.special",1297546036,["jquery.ui.datepicker","jquery.ui.dialog"]],["ext.UserBuckets",1303866948,["jquery.clickTracking","jquery.cookie","ext.UserBuckets.AccountCreationUserBucket"]],["ext.UserBuckets.AccountCreationUserBucket",1303853533,["jquery.clickTracking"]],["ext.wikiLove.icon",1313704446,[]],["ext.wikiLove.defaultOptions","1315880837",[]],["ext.wikiLove.startup","1315880837",["ext.wikiLove.defaultOptions",
"jquery.ui.dialog","jquery.ui.button","jquery.localize","jquery.elastic"]],["ext.wikiLove.local","1312944211",[]],["ext.wikiLove.init",1309455733,["ext.wikiLove.startup"]],["jquery.elastic",1313704427,[]],["ext.moodBar.init","1315880878",["jquery.cookie","jquery.client"]],["ext.moodBar.core","1315880878",["mediawiki.util","ext.moodBar.init","jquery.localize","jquery.moodBar"]],["jquery.moodBar",1311631334,["mediawiki.util"]]]);mediaWiki.config.set({"wgLoadScript":"http://bits.wikimedia.org/en.wikipedia.org/load.php","debug":false,"skin":"vector","stylepath":"http://bits.wikimedia.org/skins-1.17","wgUrlProtocols":"http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/|irc\\:\\/\\/|gopher\\:\\/\\/|telnet\\:\\/\\/|nntp\\:\\/\\/|worldwind\\:\\/\\/|mailto\\:|news\\:|svn\\:\\/\\/|git\\:\\/\\/|mms\\:\\/\\/|\\/\\/","wgArticlePath":"/wiki/$1","wgScriptPath":"/w","wgScriptExtension":".php","wgScript":"/w/index.php","wgVariantArticlePath":false,"wgActionPaths":[],"wgServer":"http://en.wikipedia.org",
"wgUserLanguage":"en","wgContentLanguage":"en","wgVersion":"1.17wmf1","wgEnableAPI":true,"wgEnableWriteAPI":true,"wgSeparatorTransformTable":["",""],"wgDigitTransformTable":["",""],"wgMainPageTitle":"Main Page","wgFormattedNamespaces":{"-2":"Media","-1":"Special","0":"","1":"Talk","2":"User","3":"User talk","4":"Wikipedia","5":"Wikipedia talk","6":"File","7":"File talk","8":"MediaWiki","9":"MediaWiki talk","10":"Template","11":"Template talk","12":"Help","13":"Help talk","14":"Category","15":"Category talk","100":"Portal","101":"Portal talk","108":"Book","109":"Book talk"},"wgNamespaceIds":{"media":-2,"special":-1,"":0,"talk":1,"user":2,"user_talk":3,"wikipedia":4,"wikipedia_talk":5,"file":6,"file_talk":7,"mediawiki":8,"mediawiki_talk":9,"template":10,"template_talk":11,"help":12,"help_talk":13,"category":14,"category_talk":15,"portal":100,"portal_talk":101,"book":108,"book_talk":109,"wp":4,"wt":5,"image":6,"image_talk":7},"wgSiteName":"Wikipedia","wgFileExtensions":["png","gif","jpg",
"jpeg","xcf","pdf","mid","ogg","ogv","svg","djvu","tiff","tif","oga"],"wgDBname":"enwiki","wgExtensionAssetsPath":"http://bits.wikimedia.org/w/extensions-1.17","wgMWSuggestTemplate":"http://en.wikipedia.org/w/api.php?action=opensearch\x26search={searchTerms}\x26namespace={namespaces}\x26suggest","wgCollectionVersion":"1.4","wgCollapsibleNavBucketTest":false,"wgCollapsibleNavForceNewVersion":false,"wgArticleFeedbackSMaxage":2592000,"wgArticleFeedbackCategories":["Article Feedback Pilot","Article Feedback","Article Feedback Additional Articles"],"wgArticleFeedbackBlacklistCategories":["Article Feedback Blacklist"],"wgArticleFeedbackLotteryOdds":100,"wgArticleFeedbackTracking":{"buckets":{"track":"0.27","ignore":"99.73"},"version":8,"expires":30,"tracked":false},"wgArticleFeedbackOptions":{"buckets":{"show":100,"hide":0},"version":8,"expires":30,"tracked":false},"wgArticleFeedbackNamespaces":[0],"wgArticleFeedbackWhatsThisPage":"Wikipedia:Article Feedback Tool","mbConfig":{"validTypes":[
"happy","sad","confused"],"userBuckets":[],"bucketConfig":{"buckets":{"feedback":80,"share":10,"editing":10},"version":3,"expires":30},"infoUrl":"http://www.mediawiki.org/wiki/MoodBar","privacyUrl":"http://wikimediafoundation.org/wiki/Feedback_policy","disableExpiration":365}});};if(isCompatible()){document.write("\x3cscript src=\"http://bits.wikimedia.org/en.wikipedia.org/load.php?debug=false\x26amp;lang=en\x26amp;modules=jquery%7Cmediawiki\x26amp;only=scripts\x26amp;skin=vector\x26amp;version=20110912T172820Z\" type=\"text/javascript\"\x3e\x3c/script\x3e");}delete isCompatible;;

/* cache key: enwiki:resourceloader:filter:minify-js:5:8c3f6f0cc5196405c5478e6396440861 */