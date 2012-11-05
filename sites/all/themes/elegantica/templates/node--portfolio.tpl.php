<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix blogpost postcontent port"<?php print $attributes; ?>>

    <div class="content"<?php print $content_attributes; ?>>


        <!-- node view full -->
        <?php if ($page): ?>
            <div class="projectdetails">			
                <div class="blogsingleimage">	
                    <?php print render($content['field_portfolio_image']); ?>

                </div>	
            </div>

            <div class="projectdescription">

                <div class="datecomment">

                    <?php
                    hide($content['body']);
                    if (isset($content['field_portfolio_category'])) {
                        hide($content['field_portfolio_category']);
                    }
                    print render($content);
                    ?>

                    <div class="portcategories"><?php print render($content['field_portfolio_category']); ?></div>							


                </div>					
                <div class="posttext"> 
                    <div> 
                        <?php print render($content['body']); ?>
                    </div>	
                </div>

                <h3 class="portsingleshare"><?php print t('Share the'); ?> <span><?php print t('project'); ?></span></h3>	
                <div class="titleborder"></div>
                <div class="socialsingle"><div class="addthis_toolbox"><div class="custom_images"><a class="addthis_button_facebook" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>"  title="Facebook"><img src="<?php print base_path() . path_to_theme(); ?>/images/facebookIcon.png" width="64" height="64" border="0" alt="Facebook" /></a>
                            <a class="addthis_button_twitter" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>"  title="Twitter"><img src="<?php print base_path() . path_to_theme(); ?>/images/twitterIcon.png" width="64" height="64" border="0" alt="Twitter" /></a>
                            <a class="addthis_button_digg" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>" title="Vimeo"><img src="<?php print base_path() . path_to_theme(); ?>/images/diggIcon.png" width="64" height="64" border="0" alt="Vimeo" /></a>
                            <a class="addthis_button_stumble" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>" title="Stumble Upon"><img src="<?php print base_path() . path_to_theme(); ?>/images/stumbleUponIcon.png" width="64" height="64" border="0" alt="Share to Stumble Upon" /></a>
                            <a class="addthis_button" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>" ><img src="<?php print base_path() . path_to_theme(); ?>/images/socialIconShareMore.png" width="64" height="64" border="0" alt="More..." /></a></div><script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js"></script></div></div>	

            </div>
        <?php print render($content['links']); ?>
        
        <?php endif; ?>
        <!-- // node view full -->


        <!-- node view teaser -->
        <?php if (!$page): ?>

            <div class="blogpostcategory">


                <div class="blogimage">	

                    <?php print render($content['field_portfolio_image']); ?>
                </div>

                <div class="entry">

                    <div class="leftholder">
                        <div class = "posted-date"><div class = "date-inside"><div class="day"><?php print format_date($node->created, 'custom', 'd') ?></div><div class="month"><?php print format_date($node->created, 'custom', 'M') ?></div></div></div>
                        <div class="commentblog"><div class = "circleHolder"><div class = "comment-inside"><a href="<?php print url('node/' . $node->nid); ?>/#comments" title="<?php print t('Comment on'); ?> <?php print $node->title; ?>"><?php print $node->comment_count; ?></a></div></div></div>
                    </div>
                    <div class = "meta">

                        <h2 class="title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
                        <div class="authorblog"><strong><?php print t('By'); ?>: <?php print theme('username', array('account' => $node)); ?></strong> </div>
                        <div class="categoryblog">
                            <?php print render($content['field_portfolio_category']); ?>
                        </div>
                        <div class="blogcontent">
                            <?php print render($content['body']); ?>
                            <?php
                            // We hide the comments and links now so that we can render them later.
                            hide($content['comments']);
                            hide($content['links']);
                            print render($content);
                            ?>
                        </div>

                        <div class="socialsingle"><div class="addthis_toolbox"><div class="custom_images"><a class="addthis_button_facebook" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>"  title="Facebook"><img src="<?php print base_path() . path_to_theme(); ?>/images/facebookIcon.png" width="64" height="64" border="0" alt="Facebook" /></a>
                                    <a class="addthis_button_twitter" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>"  title="Twitter"><img src="<?php print base_path() . path_to_theme(); ?>/images/twitterIcon.png" width="64" height="64" border="0" alt="Twitter" /></a>
                                    <a class="addthis_button_digg" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>" title="Vimeo"><img src="<?php print base_path() . path_to_theme(); ?>/images/diggIcon.png" width="64" height="64" border="0" alt="Vimeo" /></a>
                                    <a class="addthis_button_stumble" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>" title="Stumble Upon"><img src="<?php print base_path() . path_to_theme(); ?>/images/stumbleUponIcon.png" width="64" height="64" border="0" alt="Share to Stumble Upon" /></a>
                                    <a class="addthis_button" addthis:url="<?php print url('node/' . $node->nid, array('absolute' => TRUE)); ?>" addthis:title="<?php print $node->title; ?>" ><img src="<?php print base_path() . path_to_theme(); ?>/images/socialIconShareMore.png" width="64" height="64" border="0" alt="More..." /></a></div><script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js"></script></div></div>	

                        <a class="blogmore" href="<?php print url('node/' . $node->nid); ?>"><?php print t('Read more'); ?> &rarr;</a>

                    </div>

                </div>		
            </div>	

        <?php endif; ?>
        <!-- // node view teaser -->
    </div>


    <?php print render($content['comments']); ?>

</div>
