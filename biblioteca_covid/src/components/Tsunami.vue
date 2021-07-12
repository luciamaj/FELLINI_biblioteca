<template>
  <div class="container-tsunami" :class="{ 'is-invisibile': !isVisible }">
    <video hwz="on" preload="auto" id="videoTsunami">
      <source :src="'../assets/TZUNAMI_biblioteca_1-2.mp4'" type="video/mp4">
    </video>
  </div>
</template>

<style lang="scss">
  #videoTsunami {
    position: absolute; 
    right: 0; 
    bottom: 0;
    width: 100vw;
    height: 100vh;
    object-fit: contain;
  }

  .container-tsunami {
    width: 100vw;
    height: 100vh;
    position: relative;
    background-color: black;
  }

  .is-invisibile {
    opacity: 0;
  }
</style>

<script>
import JQuery from 'jquery';
let $ = JQuery;

export default {
    created: function() {
      this.$parent.$on('startTsunami', _ => {
        this.isVisible = true;
        this.initialize();
      });
    },
    props: {
      isVisible: Boolean,
    },
    methods: {  
        initialize() {
            this.videoLoop = $('#videoTsunami');
            this.backToMainIfEnded();
            
            this.loadVideo(this.videoLoop.get(0), _ => {
              this.videoLoop.get(0).play();
              console.log('play?')
            });
        },
        backToMainIfEnded() {
          this.videoLoop.get(0).addEventListener('ended', _ => {
            console.log("current index", this.currentIndex);
            console.log("data app", this.dataApp);
            this.isVisible = false;

            this.$emit('tsunamiEnded');
          },false);
        },
        loadVideo(video, videoIsLoaded) {
          video.currentTime = 0;
          video.load();
           
          video.addEventListener('loadeddata', _ => {
              videoIsLoaded();
          }, false);
        },
    },
    computed: {
      dataApp() {
        console.log(this.$store.getters.data.timeline);
        return this.$store.getters.data.timeline;
      }
    },
    mounted() {
      console.log("emitted inside");
      this.$socket.emit('inside');
      $(document).keypress(e => {
        if(e.charCode == 46) { // punto
          this.$emit('tsunamiStarted');
      }});

      this.sockets.subscribe('tsunamiStart', _ => {
        this.$emit('tsunamiStarted');
      });
    },
}
</script>