<?php

function seinfeld_lead_identity_api_call($seinfeld_form = []) {

    //Variable names altered to match $_GET variable names and API key names
    $token     = variable_get('seinfeld_api_token', '');
    $password  = variable_get('seinfeld_api_password', '');
    $offer_id  = $seinfeld_form['hasoffers_id'] ? $seinfeld_form['hasoffers_id'] : NULL;
    $ip        = ip_address();
    $useragent = urlencode($_SERVER['HTTP_USER_AGENT']);
    $url       = url(current_path(), ['absolute' => TRUE]);
    $api_url   = variable_get('kylepro_api_url', 'http://api3.cbcbackoffice.com') . '/lead/identity';

    $query_array = [
        'token' => $token,
        'password' => $password,
        'ip' => $ip,
        'useragent' => $useragent,
        'offer_id' => $offer_id,
        'url' => $url,
    ];
    
    $param_names = [
        'transaction_id',
        'affiliate_id',
        'subone',
        'subtwo',
        'subthree',
        'subfour',
        'subfive'
    ];


    //This is just for convenience for the foreach block below.
    $_GET['transaction_id'] = $_GET['transaction'] ?? NULL;

    foreach($param_names as $p) {
        if(isset($_GET[$p])) {
            $query_array[$p] = $_GET[$p];
        } else {
            unset($query_array[$p]);
        }
    }

      
    $url = $api_url . '?' . http_build_query($query_array);
    variable_set('myurl',$url);

    watchdog('seinfeld', 'Identity call sent to Seinfeld: %url.', array('%url' => $url));

    // Retreive JSON from the URL and parse.
    $res = drupal_http_request($url);
    $obj = $res->data ?? FALSE;

    return $obj ? drupal_json_decode($obj)['body']['identity'] : FALSE;
}

function get_options_array($form) {
    $elements = $form['webform']['#value']['components'];

    $options = [];
    foreach($elements as $el) {
        $options[$el['form_key']] = $el['name'];
    }
    return $options;
}

//Check if form is Seinfeld approved, return DB data if so, return FALSE if not.
function get_valid_seinfeld_form($form_id) {
    $form_info = explode('_', $form_id);
    if(count($form_info) !== 4
        || $form_info[0] !== 'webform'
        || $form_info[1] !== 'client'
        || $form_info[2] !== 'form') {
        return FALSE;
    }

    $sf = SeinfeldDao::get_form_by_id($form_info[3]);
    
    $is_valid = (isset($sf['campain_id'], $sf['hasoffers_id']));
    
    if($is_valid) {
        return $sf;
    }
    return FALSE;
}

function get_value_array($flipped = FALSE) {
     $values = [
        'enabled',
        'campaign_id',  
        'hasoffers_id', 
        'first_name',
        'last_name',  
        'phone_number', 
        'email_address',
    ];
    return $flipped ? array_flip($values) : $values;
}

function nullify_empty_strings(&$form_state) {
    foreach(get_value_array() as $key) {
        if($form_state['input'][$key] === '') {
            $form_state['input'][$key] = NULL;
        }
    }
}