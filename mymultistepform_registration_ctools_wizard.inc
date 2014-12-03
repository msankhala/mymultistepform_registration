<?php
/**
* Create callback for standard ctools registration wizard.
*/
function mymultistepform_registration_ctools_wizard($step = 'register') {
  // Include required ctools files.
  ctools_include('wizard');
  ctools_include('object-cache');
   
  $form_info = array(
  // Specify unique form id for this form.
  'id' => 'multistep_registration',
    //Specify the path for this form. It is important to include space for the $step argument to be passed.
  'path' => "user/register/%step",
    // Show breadcrumb trail.
  'show trail' => TRUE,
  'show back' => TRUE,
  'show return' => TRUE,
    // Callback to use when the 'next' button is clicked.
  'next callback' => 'mymultistepform_registration_subtask_next',
    // Callback to use when entire form is completed.
  'finish callback' => 'mymultistepform_registration_subtask_finish',
    // Callback to use when user clicks final submit button.
  'return callback' => 'mymultistepform_registration_subtask_finish',
    // Callback to use when user cancels wizard.
  'cancel callback' => 'mymultistepform_registration_subtask_cancel',
    // Specify the order that the child forms will appear in, as well as their page titles.
  'order' => array(
    'register' => t('Register'),
    'groups' => t('Connect'),
    'invite' => t('Invite'),
    ),
    // Define the child forms. Be sure to use the same keys here that were user in the 'order' section of this array.
  'forms' => array(
    'register' => array(
      'form id' => 'user_register_form'
      ),
    'groups' => array(
      'form id' => 'mymultistepform_registration_group_info_form',
        // Be sure to load the required include file if the form callback is not defined in the .module file.
      'include' => drupal_get_path('module', 'mymultistepform_registration') . '/mymultistepform_registration_groups_form.inc',
      ),
    'invite' => array(
      'form id' => 'mymultistepform_registration_invite_form',
      ),
    ),
  );
  
 
  // Make cached data available within each step's $form_state array.
  $form_state['signup_object'] = mymultistepform_registration_get_page_cache('signup');


  // Return the form as a Ctools multi-step form.
  $output = ctools_wizard_multistep_form($form_info, $step, $form_state);

  return $output;
}

/**
* Retreives an object from the cache.
*
* @param string $name
*  The name of the cached object to retreive.
*/
function mymultistepform_registration_get_page_cache($name) {
  ctools_include('object-cache');
  $cache = ctools_object_cache_get('mymultistepform_registration', $name);

 
// If the cached object doesn't exist yet, create an empty object.
  if (!$cache) {
    $cache = new stdClass();
    $cache->locked = ctools_object_cache_test('mymultistepform_registration', $name);
  }

  return $cache;
}

/**
* Creates or updates an object in the cache.
*
* @param string $name
*  The name of the object to cache.
*
* @param object $data
*  The object to be cached.
*/
function mymultistepform_registration_set_page_cache($name, $data) {
  ctools_include('object-cache');
  $cache = ctools_object_cache_set('mymultistepform_registration', $name, $data);
}

/**
* Removes an item from the object cache.
*
* @param string $name
*  The name of the object to destroy.
*/
function mymultistepform_registration_clear_page_cache($name) {
  ctools_include('object-cache');
  ctools_object_cache_clear('mymultistepform_registration', $name);
}

/**
* Callback executed when the 'next' button is clicked.
*/
function mymultistepform_registration_subtask_next(&$form_state) {
  // Store submitted data in a ctools cache object, namespaced 'signup'.
  mymultistepform_registration_set_page_cache('signup', $form_state['values']);
}

/**
* Callback executed when the 'cancel' button is clicked.
*/
function mymultistepform_registration_subtask_cancel(&$form_state) {
  // Clear our ctools cache object. It's good housekeeping.
  mymultistepform_registration_clear_page_cache('signup');
}

/**
* Callback executed when the entire form submission is finished.
*/
function mymultistepform_registration_subtask_finish(&$form_state) {
  // Clear our Ctool cache object.
  mymultistepform_registration_clear_page_cache('signup');

 
// Redirect the user to the front page.
  drupal_goto('<front>');
}

function mymultistepform_registration_invite_form($form, &$form_state) {
  $form['item'] = array(
    '#markup' => t('This is step 3'),
  );
  return $form;
}
