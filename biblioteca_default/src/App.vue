<template>
  <div id="app">  
    <router-view></router-view>
  </div>
</template>

<style lang="scss">
@import 'css/flaticon.css';
@import 'css/libs/bootstrap.min.css';
@import 'scss/style.scss';
</style>

<script>
import { store } from './store/store.js'
import JQuery from 'jquery';
let $ = JQuery;

export default {
  name: 'app',
  store,
  components: { },
  created () {
  },
  methods: {
  },
  mounted() {
  },
  sockets: {
    connect: function() {
      console.log('socket connected');
    },
  }
}
</script>