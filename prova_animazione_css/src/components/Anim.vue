<template>
  <div class="container-anim">
    <div class="wrapper">
    
    <div class="rotate">
        <a href="https://ricostacruz.com/jquery.transit/">jQuery Transit</a>
        
    </div>
    </div>

    <h3>Experiment with jQuery Transit</h3>
    <p>Using chaining transition with easing effect</p>

    <div class="transition"></div>
  </div>
</template>
<script>
import JQuery from 'jquery';
require('jquery.transit')
let $ = JQuery;

export default {
    methods: {  
        initialize() {
              setInterval( function() {
                $('.rotate')
                .transition({
                    rotate: '180deg',
                    scale: 2.5
                }, 1500, 'cubic-bezier(0, 0.9, 0.3, 1)')
                .transition({
                    x: -40,
                    y: 100
                })
                .transition({
                    rotate: '0deg',
                    scale: 1
                }, 1000, 'easeInOutCubic')
                .transition({
                    x: 50,
                    y: 20,
                    scale: 1.5,
                    rotate: '-90deg'
                }, 500, 'easeOutQuint')      
                .transition({
                    x: 0,
                    y: 0,
                    scale: 1,
                    rotate: '0deg'
                }, 1000, 'easeOutQuint');
            }, 2000);

            setInterval(function() {
                $('h3')
                .transition({
                    scale: 1.05
                }, 200)
                .transition({
                    scale: 0.7
                }, 100)
                .transition({
                    x: 0,
                    y: 0,
                    scale: 1
                }, 200)    
            }, 100);

            setInterval(function() {
                $('.transition')
                .transition({
                    opacity: 1
                }, 500)
                .transition({
                    opacity: 0
                }, 500) 
            }, 1000);
        },
    },
    computed: {
      //
    },
    mounted() {
        this.initialize();
    },
    data() {
        return {
          premuto: false,
          playbackRate: 1,
        };
    }
}
</script>