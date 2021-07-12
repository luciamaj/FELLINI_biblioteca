// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import App from './App.vue'
import router from './router'
import 'popper.js';
import 'jquery';
import 'bootstrap';
import { i18n } from './plugins/i18n.js';
import { store } from './store/store.js'
import VueSocketIO from 'vue-socket.io';
import SocketIO from "socket.io-client";

import LoadScript from 'vue-plugin-load-script';

Vue.use(LoadScript);
Vue.use(new VueSocketIO({
  debug: true,
  connection: SocketIO('http://localhost:4000'),
  vuex: {
    store,
  },
}));

Vue.config.productionTip = false
let dataUrl = "../data/data.js";

Vue.loadScript(dataUrl)
.then(_ => {
  store.commit("dataSet", data);
  
  new Vue({
    el: '#app',
    router,
    i18n,
    store,
    template: '<App/>',
    components: { App },
  });
})
.catch((error) => {
  console.log("ERROR LOADING APP DATA AT", data, error);
});