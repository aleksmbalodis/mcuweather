import styles from "../styles/Navbar.module.css"
import Link from "next/link"
import Image from 'next/image'


export default function Navbar({ children, home }) {
    return (
        <div className={styles.navbar}>
            <ul>
                <li><Link href="/"><a>Weather control</a></Link></li>
                <li><Link href="/data"><a>Data</a></Link></li>
                <li><Link href="/graphs"><a>Graphs</a></Link></li>
            </ul>
        </div>
    )
}