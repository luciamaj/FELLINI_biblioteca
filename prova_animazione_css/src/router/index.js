import Vue from 'vue';
import Router from 'vue-router';
import Home from './../components/Home.vue';
import Rfid from './../components/Rfid.vue';
import Loop from './../components/Loop.vue';
import Anim from './../components/Anim.vue';

Vue.use(Router);

const router = new Router({
  routes: [
    {
      path: '/',
      name: 'anim',
      component: Anim
    }
  ]
})

export default router;