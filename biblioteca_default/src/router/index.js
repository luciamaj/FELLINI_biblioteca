import Vue from 'vue';
import Router from 'vue-router';
import Rfid from './../components/Rfid.vue';

Vue.use(Router);

const router = new Router({
  routes: [
    {
      path: '/',
      name: 'rfid',
      component: Rfid
    },
  ]
})

export default router;