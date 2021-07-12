import Vue from 'vue';
import Router from 'vue-router';
import Loop from './../components/Loop.vue';

Vue.use(Router);

const router = new Router({
  routes: [
    {
      path: '/',
      name: 'loop',
      component: Loop
    }
  ]
})

export default router;