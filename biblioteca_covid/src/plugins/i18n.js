import Vue from 'vue';
import VueI18n from 'vue-i18n';
import { it } from './../lang/it.js'
import { en } from './../lang/en.js'

Vue.use(VueI18n);
const messages = {  'it': it, 'en': en};
export let i18n = new VueI18n({locale: 'it',  fallbackLocale: 'en',  messages});
