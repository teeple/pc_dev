// Created by iWeb 3.0.3 local-build-20110426

function writeMovie1()
{detectBrowser();if(windowsInternetExplorer)
{document.write('<object id="id5" classid="clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B" codebase="http://www.apple.com/qtactivex/qtplugin.cab" width="611" height="398" style="height: 398px; left: 44px; position: absolute; top: 379px; width: 611px; z-index: 1; "><param name="src" value="../../../../Media/AccountManagment.mov" /><param name="controller" value="true" /><param name="autoplay" value="false" /><param name="scale" value="tofit" /><param name="volume" value="100" /><param name="loop" value="false" /></object>');}
else if(isiPhone)
{document.write('<object id="id5" type="video/quicktime" width="611" height="398" style="height: 398px; left: 44px; position: absolute; top: 379px; width: 611px; z-index: 1; "><param name="src" value="1_Account_Management_files/AccountManagment-1.jpg"/><param name="target" value="myself"/><param name="href" value="../../../../../Media/AccountManagment.mov"/><param name="controller" value="true"/><param name="scale" value="tofit"/></object>');}
else
{document.write('<object id="id5" type="video/quicktime" width="611" height="398" data="../../../../Media/AccountManagment.mov" style="height: 398px; left: 44px; position: absolute; top: 379px; width: 611px; z-index: 1; "><param name="src" value="../../../../Media/AccountManagment.mov"/><param name="controller" value="true"/><param name="autoplay" value="false"/><param name="scale" value="tofit"/><param name="volume" value="100"/><param name="loop" value="false"/></object>');}}
setTransparentGifURL('../../../../Media/transparent.gif');function applyEffects()
{var registry=IWCreateEffectRegistry();registry.registerEffects({stroke_0:new IWStrokeParts([{rect:new IWRect(-2,2,4,196),url:'1_Account_Management_files/stroke.png'},{rect:new IWRect(-2,-2,4,4),url:'1_Account_Management_files/stroke_1.png'},{rect:new IWRect(2,-2,416,4),url:'1_Account_Management_files/stroke_2.png'},{rect:new IWRect(418,-2,4,4),url:'1_Account_Management_files/stroke_3.png'},{rect:new IWRect(418,2,4,196),url:'1_Account_Management_files/stroke_4.png'},{rect:new IWRect(418,198,4,4),url:'1_Account_Management_files/stroke_5.png'},{rect:new IWRect(2,198,416,4),url:'1_Account_Management_files/stroke_6.png'},{rect:new IWRect(-2,198,4,4),url:'1_Account_Management_files/stroke_7.png'}],new IWSize(420,200))});registry.applyEffects();}
function hostedOnDM()
{return false;}
function onPageLoad()
{dynamicallyPopulate();loadMozillaCSS('1_Account_Management_files/1_Account_ManagementMoz.css')
adjustLineHeightIfTooBig('id1');adjustFontSizeIfTooBig('id1');adjustLineHeightIfTooBig('id2');adjustFontSizeIfTooBig('id2');adjustLineHeightIfTooBig('id3');adjustFontSizeIfTooBig('id3');adjustLineHeightIfTooBig('id4');adjustFontSizeIfTooBig('id4');adjustLineHeightIfTooBig('id6');adjustFontSizeIfTooBig('id6');adjustLineHeightIfTooBig('id7');adjustFontSizeIfTooBig('id7');adjustLineHeightIfTooBig('id8');adjustFontSizeIfTooBig('id8');Widget.onload();fixupAllIEPNGBGs();fixAllIEPNGs('../../../../Media/transparent.gif');BlogFixupPreviousNext();applyEffects()}
function onPageUnload()
{Widget.onunload();}
