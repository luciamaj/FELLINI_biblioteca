<template>
  <div id="app">  
    <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.11.2/css/all.css" rel="stylesheet">
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
  }
}
</script>