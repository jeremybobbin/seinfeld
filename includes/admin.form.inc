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

function seinfeld_tab_form(&$form) {
  $options = [NULL => '-'] + get_options_array($form);
  $defaults = SeinfeldDao::get_form_by_id($form['nid']['#value']);

  $form['#submit'][] = 'seinfeld_submit_handler';
  $form['#validate'][] = 'seinfeld_validator';

  $form['seinfeld'] = [
    '#type' => 'fieldset',
    '#title' => 'Seinfeld',
    '#group' => 'additional_settings',
    '#attributes' => [
      'class' => 'node-form-seinfeld'
    ],
    'enabled' => [
      '#type' => 'checkbox',
      '#title' => 'Enable Seinfeld CRM on this form',
      '#default_value' => $defaults['enabled'],
    ],
    'link' => [
      '#type' => 'container',
      '#parents' => ['seinfeld'],
      'campaign_id' => [
        '#type' => 'textfield',
        '#title' => 'Campaign ID',
        '#default_value' => $defaults['campaign_id'],
        '#maxlength' => 5,
      ],
      'hasoffers_id' => [
        '#type' => 'textfield',
        '#title' => 'HasOffers Offer ID',
        '#default_value' => $defaults['hasoffers_id'],
        '#maxlength' => 5,
      ],
      'first_name' => [
        '#type' => 'select',
        '#title' => 'First Name Field',
        '#options' => $options,
        '#default_value' => $defaults['first_name'],
      ],
      'last_name' => [
        '#type' => 'select',
        '#title' => 'Last Name Field',
        '#options' => $options,
        '#default_value' => $defaults['last_name'],
      ],
      'phone_number' => [
        '#type' => 'select',
        '#title' => 'Phone Number Field',
        '#options' => $options,
        '#default_value' => $defaults['phone_number'],
      ],
      'email_address' => [
        '#type' => 'select',
        '#title' => 'Email Address Field',
        '#options' => $options,
        '#default_value' => $defaults['email_address'],
      ],
    ],
  ];
}

//65535 is max int for now.
function seinfeld_validator($form, &$form_state) {
  nullify_empty_strings($form_state);

  $values = $form_state['input'];

  if($values['hasoffers_id'] > 65535) {
    form_set_error('hasoffers_id', 'Offer ID cannot be larger than 65,535');
  }
  if ($values['campaign_id'] > 65535) {
    form_set_error('campaign_id', 'Campaign ID cannot be larger than 65,535');
  }
  if($values['enabled'] && $values['hasoffers_id'] === NULL) {
    form_set_error('hasoffers_id', 'You must enter a valid Campaign ID if you want to enable Seinfeld.');
  }
  if($values['enabled'] && $values['campaign_id'] === NULL) {
    form_set_error('campaign_id', 'You must enter a valid Offer ID if you want to enable Seinfeld.');
  }
}