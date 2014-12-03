<?php
function mymultistepform_registration_group_info_form($form, &$form_state) {
  $form['item'] = array(
    '#markup' => t('This is step 2'),
  );
  return $form;
}