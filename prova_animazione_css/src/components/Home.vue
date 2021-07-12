<template>
  <div class="Home">
      <div class="container">
        <div class="spacer">
          <div>
            <router-link to="rfid">RFID</router-link>
          </div>
          <div>
            <router-link to="loop">LOOP</router-link>
          </div>
        </div>
      </div>
  </div>
</template>
<script>

import { recievedDatiConfig } from './../plugins/socket.js'

export default {
    components: { },
    data () {
        return {
            name: 'Home',
            description: 'Questa è la home'
        }
    },
    computed: {
      //
    },
    mounted() {
    },
    created() {
      this.datiConfig();
    },
    methods: {
      datiConfig() {
        //recievedDatiConfig();
      }
    }
  }
</script>