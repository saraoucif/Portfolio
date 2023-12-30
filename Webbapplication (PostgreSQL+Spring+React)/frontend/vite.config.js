import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
      react(),
  ],
  server: {
    proxy: {
      '/api': {
        target: 'http://35.222.169.45:8080/',
        changeOrigin: true,
        secure: false,

      }
    },
    build: {
      minify: false,
    css: {
      include: [
        'src/components/Table.css'
      ]
    }
  }
  }
})