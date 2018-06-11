<?php

function get_seinfeld_form_with_id($id) {
    return db_select('seinfeld_forms', 'sf')
        ->fields('sf', ['form_id'])
        ->condition('sf.form_id', $id,'=')
        ->execute()
        ->fetchAssoc();
}

function seinfeld_lead_identity_api_call($seinfeld_form = []) {
    $token    = variable_get('seinfeld_api_token', '');
    $password = variable_get('seinfeld_api_password', '');
  
    $hasoffers_id   = $seinfeld_form['hasoffers_id'];
    $ip_address     = ip_address();
    $user_agent     = urlencode($_SERVER['HTTP_USER_AGENT']);
    $current_url    = url(current_path(), ['absolute' => TRUE]);
  }