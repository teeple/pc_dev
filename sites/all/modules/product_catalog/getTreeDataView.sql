/* prepare sequence. It should be executed only once */
DROP TABLE pc_dev.get_tree_data_view_sequence;
CREATE TABLE pc_dev.get_tree_data_view_sequence(
	seq_num int auto_increment primary key
);

/* declare procedure */
DROP PROCEDURE IF EXISTS pc_dev.getTreeDataView;
DROP PROCEDURE IF EXISTS pc_dev._getTreeDataView;

DELIMITER $$

CREATE PROCEDURE pc_dev.getTreeDataView(IN rootNid INT)
BEGIN
	DECLARE SEQ_NUM INT;
	DECLARE TEMP_TABLE_NAME VARCHAR(50);
	
	-- get seq
	INSERT INTO pc_dev.get_tree_data_view_sequence values();
	SELECT LAST_INSERT_ID() INTO SEQ_NUM;

	-- create temp table	
	SET TEMP_TABLE_NAME = CONCAT('get_tree_data_view_sequence',CONVERT(SEQ_NUM,CHAR(10)));	
	SET @stmt_create = CONCAT('CREATE TABLE ',TEMP_TABLE_NAME,' (level int, nid int primary key not null, content_type varchar(128), rel_type varchar(128), parent_nid int, weight int, title varchar(255))');
	PREPARE CREATE_TABLE FROM @stmt_create; 
	EXECUTE CREATE_TABLE;
	DEALLOCATE PREPARE CREATE_TABLE;
	
	-- call recursive function
	SET max_sp_recursion_depth=200;
	CALL pc_dev._getTreeDataView(rootNid,0,TEMP_TABLE_NAME);

	-- fetch tree data
	SET @stmt_select = CONCAT('SELECT * FROM ',TEMP_TABLE_NAME,' ORDER BY level asc, parent_nid asc, weight desc');
	PREPARE SELECT_DATA FROM @stmt_select;
	EXECUTE SELECT_DATA;
	DEALLOCATE PREPARE SELECT_DATA;

	-- drop temp table
	SET @stmt_drop = CONCAT('DROP TABLE ',TEMP_TABLE_NAME);
	PREPARE DROP_TABLE FROM @stmt_drop;
	EXECUTE DROP_TABLE;
	DEALLOCATE PREPARE DROP_TABLE;
	
END $$

CREATE PROCEDURE pc_dev._getTreeDataView(IN parent_nid INT,IN TREE_LEVEL INT,IN TEMP_TABLE_NAME VARCHAR(50))
BEGIN
	DECLARE NODE_NID INT;
	DECLARE NODE_PARENT_NID INT;
	DECLARE NODE_CONTENT_TYPE VARCHAR(128);
	DECLARE NODE_REL_TYPE VARCHAR(128);
	DECLARE NODE_WEIGHT INT;
	DECLARE NODE_TITLE VARCHAR(255);

	DECLARE NODE_COUNT INT DEFAULT 0;

	DECLARE CURSOR_DONE INT DEFAULT 0;	
	DECLARE CURSOR_NODE CURSOR FOR
			 SELECT entity_id
			   FROM pc_dev.field_data_field_parent_node
			  WHERE field_parent_node_nid = parent_nid;				 
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET CURSOR_DONE = 1;
	
	-- insert parent node
	SELECT count(*) into NODE_COUNT
	  FROM pc_dev.field_data_field_parent_node
     WHERE entity_id = parent_nid
       AND bundle NOT IN ('basicrate_idd','basicrate_domestic','treenodecounterforvoucher');

	IF NODE_COUNT > 0 THEN
					SELECT parent.entity_id,parent.field_parent_node_nid,parent.bundle 
							,CASE 
								 WHEN parent.bundle = 'defaulttreenode' THEN
									  IFNULL(
										(SELECT field_rel_type_value 
										   FROM  field_data_field_rel_type
										  WHERE entity_id = (SELECT field_ref_tree_node_tid_value 
															  FROM field_data_field_ref_tree_node_tid
																 WHERE entity_id = parent_nid)
										  ),
									  parent.bundle)
								 WHEN parent.bundle = 'treenodecounter' THEN
									  CONCAT('tree_node_',
												(SELECT type
												   FROM node
												  WHERE nid =	(SELECT field_ref_counter_nid
																   FROM field_data_field_ref_counter
																  WHERE entity_id = parent_nid)
												),'_',
												LOWER(
													(SELECT name
													   FROM taxonomy_term_data
													  WHERE tid = (SELECT field_main_or_accumulated_tid 
																	  FROM field_data_field_main_or_accumulated
																	 WHERE entity_id = parent_nid
																	)
													)
												),'_',
												LOWER(
													(SELECT name
													   FROM taxonomy_term_data
													  WHERE tid = (SELECT field_counter_type_tid 
																	  FROM field_data_field_counter_type
																	 WHERE entity_id = (SELECT field_ref_counter_nid
																							FROM field_data_field_ref_counter
																						   WHERE entity_id = parent_nid)
																	)
													)
												)
									 )
								 WHEN parent.bundle = 'treenodewithnodereference' THEN
									  CONCAT('treenode_',
											  (SELECT type
												 FROM node
												WHERE nid =	(SELECT field_ref_node_nid
																   FROM field_data_field_ref_node
																  WHERE entity_id = parent_nid)
											   )
									  )
								 WHEN parent.bundle = 'treenodegeneral' THEN
									  (SELECT field_rel_type_value
										 FROM field_data_field_rel_type
										WHERE entity_id = parent_nid
									  )								 
								 ELSE parent.bundle
							  END
							,IFNULL(weight.field_weight_value,0)
							,CASE 
								  WHEN parent.bundle = 'defaulttreenode' THEN 
										(SELECT name 
										   FROM pc_dev.taxonomy_term_data
										  WHERE tid = (SELECT field_ref_tree_node_tid_value
														  FROM field_data_field_ref_tree_node_tid 
														 WHERE entity_id = parent_nid)
										)
								  WHEN parent.bundle = 'treenodecounter' THEN	
										(SELECT title
										   FROM node
										  WHERE nid =	(SELECT field_ref_counter_nid
														   FROM field_data_field_ref_counter
														  WHERE entity_id = parent_nid)
										)
								  WHEN parent.bundle = 'treenodewithnodereference' THEN	
										(SELECT title
										   FROM node
										  WHERE nid =	(SELECT field_ref_node_nid
														   FROM field_data_field_ref_node
														  WHERE entity_id = parent_nid)
										)	
								  ELSE node.title 			  
							 END
					  INTO NODE_NID, NODE_PARENT_NID, NODE_CONTENT_TYPE, NODE_REL_TYPE, NODE_WEIGHT, NODE_TITLE
					  FROM pc_dev.field_data_field_parent_node parent
				INNER JOIN pc_dev.node node 
		  LEFT OUTER JOIN pc_dev.field_data_field_weight weight
						ON parent.entity_id = weight.entity_id
					 WHERE parent.entity_id = parent_nid
					   AND parent.entity_id = node.nid
					   AND parent.bundle NOT IN ('basicrate_idd','basicrate_domestic','treenodecounterforvoucher');
	ELSE 
		IF TREE_LEVEL = 0 THEN
			-- Only for root
			SELECT node.nid,0,node.type
				   , CASE 
						 WHEN node.type = 'defaulttreenode' THEN
							  IFNULL(
								(SELECT field_rel_type_value 
								   FROM  field_data_field_rel_type
								  WHERE entity_id = (SELECT field_ref_tree_node_tid_value 
													  FROM field_data_field_ref_tree_node_tid
														 WHERE entity_id = parent_nid)
								  ),
							  node.type)
						 WHEN node.type = 'treenodecounter' THEN
							  CONCAT('tree_node_',
										(SELECT type
										   FROM node
										  WHERE nid =	(SELECT field_ref_counter_nid
														   FROM field_data_field_ref_counter
														  WHERE entity_id = parent_nid)
										),'_',
										LOWER(
											(SELECT name
											   FROM taxonomy_term_data
											  WHERE tid = (SELECT field_main_or_accumulated_tid 
															  FROM field_data_field_main_or_accumulated
															 WHERE entity_id = parent_nid
															)
											)
										),'_',
										LOWER(
											(SELECT name
											   FROM taxonomy_term_data
											  WHERE tid = (SELECT field_counter_type_tid 
															  FROM field_data_field_counter_type
															 WHERE entity_id = (SELECT field_ref_counter_nid
																					FROM field_data_field_ref_counter
																				   WHERE entity_id = parent_nid)
															)
											)
										)
							 )
						 WHEN node.type = 'treenodewithnodereference' THEN
							  CONCAT('treenode_',
									  (SELECT type
										 FROM node
										WHERE nid =	(SELECT field_ref_node_nid
														   FROM field_data_field_ref_node
														  WHERE entity_id = parent_nid)
									   )
							  )
						 WHEN node.type = 'treenodegeneral' THEN
							  (SELECT field_rel_type_value
								 FROM field_data_field_rel_type
								WHERE entity_id = parent_nid
							  )						 
						 ELSE node.type
					  END
				   , IFNULL(weight.field_weight_value,0)
                 ,CASE 
						WHEN node.type = 'defaulttreenode' THEN 
							(SELECT name 
							   FROM pc_dev.taxonomy_term_data
							  WHERE tid = (SELECT field_ref_tree_node_tid_value
											  FROM field_data_field_ref_tree_node_tid 
											 WHERE entity_id = parent_nid)
							)
						WHEN node.type = 'treenodecounter' THEN	
							(SELECT title
							   FROM node
							  WHERE nid =	(SELECT field_ref_counter_nid
											   FROM field_data_field_ref_counter
											  WHERE entity_id = parent_nid)
							)
						WHEN node.type = 'treenodewithnodereference' THEN	
							(SELECT title
							   FROM node
							  WHERE nid =	(SELECT field_ref_node_nid
											   FROM field_data_field_ref_node
											  WHERE entity_id = parent_nid)
							)	
						ELSE node.title
                  END
                 INTO NODE_NID, NODE_PARENT_NID, NODE_CONTENT_TYPE, NODE_REL_TYPE, NODE_WEIGHT, NODE_TITLE
			  FROM pc_dev.node node 
  LEFT OUTER JOIN pc_dev.field_data_field_weight weight
				ON node.nid= weight.entity_id
			 WHERE node.nid = parent_nid;			   
		END IF;
	END IF;

	-- select NODE_NID,NODE_PARENT_NID,NODE_CONTENT_TYPE,NODE_WEIGHT;
	
	IF NODE_NID != '' AND NODE_NID IS NOT NULL AND NODE_CONTENT_TYPE IS NOT NULL AND NODE_REL_TYPE IS NOT NULL AND NODE_WEIGHT IS NOT NULL AND NODE_TITLE IS NOT NULL THEN
		SET @stmt_insert = CONCAT('INSERT INTO ',TEMP_TABLE_NAME,' VALUES (',TREE_LEVEL,'\,',NODE_NID,'\,\'',NODE_CONTENT_TYPE,'\'\,\'',NODE_REL_TYPE,'\'\,',NODE_PARENT_NID,'\,',NODE_WEIGHT,'\,\'',NODE_TITLE,'\')');

		PREPARE INSERT_ROW FROM @stmt_insert;
		EXECUTE INSERT_ROW;
		DEALLOCATE PREPARE INSERT_ROW;
		
		
		OPEN CURSOR_NODE;
			CURSOR_LOOP: LOOP
				FETCH CURSOR_NODE INTO NODE_NID;
				IF CURSOR_DONE THEN
					LEAVE CURSOR_LOOP;
				END IF;
				CALL pc_dev._getTreeDataView(NODE_NID,TREE_LEVEL+1,TEMP_TABLE_NAME);
			END LOOP;
		CLOSE CURSOR_NODE;
	END IF;
END $$

DELIMITER ;