<?php

function seinfeld_admin_settings() {
    
    $form['#submit'][] = 'seinfeld_admin_submitter';

    $form['seinfeld_api_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Seinfeld API Url'),
      '#description' => t('The Seinfeld API base url'),
      '#default_value' => variable_get('seinfeld_api_url', 'http://api3.cbcbackoffice.com'),
      '#required' => TRUE,
      '#size' => 30,
    );
  
    $form['seinfeld_api_token'] = array(
      '#type' => 'textfield',
      '#title' => t('Seinfeld API Token'),
      '#description' => t('The API token used to connect to the Seinfeld system'),
      '#default_value' => variable_get('seinfeld_api_token', ''),
      '#required' => TRUE,
      '#size' => 30,
    );
  
    $form['seinfeld_api_password'] = array(
      '#type' => 'textfield',
      '#title' => t('Seinfeld API Password'),
      '#description' => t('The API password used to connect to the Seinfeld system'),
      '#default_value' => variable_get('seinfeld_api_password', ''),
      '#required' => TRUE,
      '#size' => 30,
    );
  
    return system_settings_form($form);
}