import '../styles/globals.css'
import Navbar from '../components/navbar'

function MyApp({ Component, pageProps }) {
  return (
  <>
    <Navbar/>
    {/* {console.log(Component)} */}
    <Component {...pageProps} />
  </>)
}

export default MyApp
