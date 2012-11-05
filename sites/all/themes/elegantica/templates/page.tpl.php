<div id="headerwrap">
    <div id="header">
        <!-- ***************** - LOGO - ***************** -->
        <?php if ($site_name || $site_slogan): ?>
            <div id="logo">
                <?php if ($logo): ?>
                    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
                        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                    </a>
                <?php endif; ?>

                <?php if ($site_slogan): ?>
                    <div class="logotag">
                        <?php print $site_slogan; ?>
                    </div>
                <?php endif; ?>
            </div>
        <?php endif; ?>
        <!-- ***************** - NAVIGATION MENU - ***************** -->	

        <?php if ($page['header']): ?>
            <div class="pagenav">
                <div class="menu-header">
                    <?php print render($page['header']); ?>
                </div>
            </div>
        <?php endif; ?>
    </div>

    <div id="second_menu">
    </div>

    <!-- modified by khg98 : moving the sub menu to header -->
        <div class="pagewrap">
            <div class="pagecontent">
                <div class="pagecontentContent">
                <!-- modified by khg98 : showing sub menu -->
                <?php $a = strstr(render($page['sidebar_second']), "<h2>"); 
                    $b = substr($a, 4); $c = explode('<', $b);
                 ?> 
                    <!--<?php print render($title_prefix); ?> -->
                    <h2 class="title" id="page-title"><?php print $c[0]; ?></h2>
                    <!-- <?php print render($title_suffix); ?> -->

                    <!--
                    <?php if ($breadcrumb): ?>
                        <div id="breadcrumb"><?php print $breadcrumb; ?></div>
                    <?php endif; ?>
                    -->
                </div>
<!-- modified by khg98 -->
                <!--div class="homeIcon"><a href="<?php print $front_page; ?>"></a></div-->
            </div>

        </div>
</div>




<!-- modified by khg98 : showing any circumstances -->
<!--?php if ($title): ?-->
    <div class="outerpagewrap">
    </div>
<div class="clear"></div>

<!--?php endif; ?-->

<?php print $messages; ?>


<!-- ***************** - SLIDESHOW - ***************** -->
<?php if ($page['highlighted']): ?>
    <div id="highlighted"><div class="section clearfix">
            <?php print render($page['highlighted']); ?>
        </div></div>
<?php endif; ?>

<?php
$home_class = 'not-homewrap';
if (drupal_is_front_page()) {
    $home_class = 'homewrap';
}
?>

<div id="mainwrap" class="<?php print $home_class; ?>">

    <div id="main" class="clearfix">
        <?php print $messages; ?>   
        
        <!-- modified by khg98 : changing the sidebar order -->
        
        <?php if ($page['sidebar_second']): ?>
            <div id="sidebar-second" class="sidebar"><div class="section">
                    <?php print render($page['sidebar_second']); ?>
                </div></div>
            <div style="float:left;" id="sidebar_toggle_trigger">&#60;</div>
        <?php endif; ?>

        <div id="content"><div class="section">

                <?php if (!empty($tabs)): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
                <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                <div class="clear"></div>
                
                <?php print render($page['content']); ?>
                <?php print $feed_icons; ?>
            </div>
        </div>


        <div class="clear"></div>
    </div>
</div>
<!-- ***************** - START OF FOOTER - ***************** -->
<div id="footer">
    <div class="totop">
        <div class="gototop">
            <div class="arrowgototop"></div>
        </div>
    </div>

    <div class="fshadow"></div>
    <?php if ($page['footer_firstcolumn'] || $page['footer_secondcolumn'] || $page['footer_thirdcolumn'] || $page['footer_fourthcolumn']): ?>
        <div id="footerinside">
            <div class="footer_widget">

                <?php if ($page['footer_firstcolumn']): ?>
                    <div class="footer_widget1">
                        <?php print render($page['footer_firstcolumn']); ?>
                    </div>
                <?php endif; ?>




                <?php if ($page['footer_secondcolumn']): ?>
                    <div class="footer_widget2">
                        <?php print render($page['footer_secondcolumn']); ?>

                    </div>
                <?php endif; ?>


                <div class="footer_widget3">
                    <?php print render($page['footer_thirdcolumn']); ?>

                </div>

                <?php if ($page['footer_fourthcolumn']): ?>
                    <div class="footer_widget4 last">
                        <?php print render($page['footer_fourthcolumn']); ?>
                    </div>
                <?php endif; ?>
            </div>
        </div>
    <?php endif; ?>

    <div id="footerbwrap">
        <div id="footerb">
            <?php print render($page['footer']); ?>

        </div>
    </div>
</div>

