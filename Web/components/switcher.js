import styles from "../styles/Switcher.module.css"

export default function Switcher({graphs}) {


    return (
        <div className={styles.page}>
            <ul>
                <li><a href="#home">Brightness</a></li>
                <li><a href="#news">Humidity</a></li>
                <li><a href="#contact">Temperature</a></li>
            </ul>
            <div style={{}}>
                <h2>Fixed Full-height Side Nav</h2>
                <h3>Try to scroll this area, and see how the sidenav sticks to the page</h3>
                <p>Notice that this div element has a left margin of 25%. This is because the side navigation is set to 25% width. If you remove the margin, the sidenav will overlay/sit on top of this div.</p>
                <p>Also notice that we have set overflow:auto to sidenav. This will add a scrollbar when the sidenav is too long (for example if it has over 50 links inside of it).</p>
                <p>Some text..</p>
                <p>Some text..</p>
                <p>Some text..</p>
                <p>Some text..</p>
                <p>Some text..</p>
                <p>Some text..</p>
                <p>Some text..</p>
            </div>
        </div>
    )
}