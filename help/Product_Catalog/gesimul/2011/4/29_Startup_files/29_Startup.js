// Created by iWeb 3.0.3 local-build-20110426

function writeMovie1()
{detectBrowser();if(windowsInternetExplorer)
{document.write('<object id="id5" classid="clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B" codebase="http://www.apple.com/qtactivex/qtplugin.cab" width="555" height="363" style="height: 363px; left: 72px; position: absolute; top: 250px; width: 555px; z-index: 1; "><param name="src" value="../../../../Media/Start%26Login.mov" /><param name="controller" value="true" /><param name="autoplay" value="false" /><param name="scale" value="tofit" /><param name="volume" value="100" /><param name="loop" value="false" /></object>');}
else if(isiPhone)
{document.write('<object id="id5" type="video/quicktime" width="555" height="363" style="height: 363px; left: 72px; position: absolute; top: 250px; width: 555px; z-index: 1; "><param name="src" value="29_Startup_files/Start%26Login-1.jpg"/><param name="target" value="myself"/><param name="href" value="../../../../../Media/Start%26Login.mov"/><param name="controller" value="true"/><param name="scale" value="tofit"/></object>');}
else
{document.write('<object id="id5" type="video/quicktime" width="555" height="363" data="../../../../Media/Start%26Login.mov" style="height: 363px; left: 72px; position: absolute; top: 250px; width: 555px; z-index: 1; "><param name="src" value="../../../../Media/Start%26Login.mov"/><param name="controller" value="true"/><param name="autoplay" value="false"/><param name="scale" value="tofit"/><param name="volume" value="100"/><param name="loop" value="false"/></object>');}}
setTransparentGifURL('../../../../Media/transparent.gif');function applyEffects()
{var registry=IWCreateEffectRegistry();registry.registerEffects({stroke_0:new IWStrokeParts([{rect:new IWRect(-2,2,4,151),url:'29_Startup_files/stroke.png'},{rect:new IWRect(-2,-2,4,4),url:'29_Startup_files/stroke_1.png'},{rect:new IWRect(2,-2,322,4),url:'29_Startup_files/stroke_2.png'},{rect:new IWRect(324,-2,4,4),url:'29_Startup_files/stroke_3.png'},{rect:new IWRect(324,2,4,151),url:'29_Startup_files/stroke_4.png'},{rect:new IWRect(324,153,4,5),url:'29_Startup_files/stroke_5.png'},{rect:new IWRect(2,153,322,5),url:'29_Startup_files/stroke_6.png'},{rect:new IWRect(-2,153,4,5),url:'29_Startup_files/stroke_7.png'}],new IWSize(326,155))});registry.applyEffects();}
function hostedOnDM()
{return false;}
function onPageLoad()
{dynamicallyPopulate();loadMozillaCSS('29_Startup_files/29_StartupMoz.css')
adjustLineHeightIfTooBig('id1');adjustFontSizeIfTooBig('id1');adjustLineHeightIfTooBig('id2');adjustFontSizeIfTooBig('id2');adjustLineHeightIfTooBig('id3');adjustFontSizeIfTooBig('id3');adjustLineHeightIfTooBig('id4');adjustFontSizeIfTooBig('id4');adjustLineHeightIfTooBig('id6');adjustFontSizeIfTooBig('id6');adjustLineHeightIfTooBig('id7');adjustFontSizeIfTooBig('id7');Widget.onload();fixupAllIEPNGBGs();fixAllIEPNGs('../../../../Media/transparent.gif');BlogFixupPreviousNext();applyEffects()}
function onPageUnload()
{Widget.onunload();}
