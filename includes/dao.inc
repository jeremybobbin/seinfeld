<?php

class SeinfeldDao {
    public static function get_form_by_id($id) {
        return db_select('seinfeld_forms', 'sf')
            ->fields('sf')
            ->condition('sf.form_id', $id,'=')
            ->execute()
            ->fetchAssoc();
    }

    public static function update_form_by_id($nid, $values) {
        return db_update('seinfeld_forms')
            ->fields(self::generate_fields($values))
            ->condition('form_id', $nid,'=')
            ->execute();
    }

    public static function insert_form($nid, $values) {
        $fields = ['form_id' => $nid] + self::generate_fields($values);
        dsm($fields);
        return db_insert('seinfeld_forms')
            ->fields($fields)
            ->execute();
    }

    //Determines if 'update' or 'insert' should be used
    public static function put_form($nid, $values) {
        if(self::get_form_by_id($nid)) {
            return self::update_form_by_id($nid, $values);
        } else {
            return self::insert_form($nid, $values);
        }
    }

    private static function generate_fields($values) {
        $fields = get_value_array(TRUE);
        foreach($fields as $k => $f) {
            $fields[$k] = $values[$k];
        }
        return $fields;
    }
}