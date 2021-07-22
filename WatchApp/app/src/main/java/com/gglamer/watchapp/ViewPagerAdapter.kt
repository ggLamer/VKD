import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentPagerAdapter
import com.gglamer.watchapp.ButtonsFragment
import com.gglamer.watchapp.HumidityFragment
import com.gglamer.watchapp.TempFragment

class ViewPagerAdapter(fm: FragmentManager) : FragmentPagerAdapter(fm) {
    override fun getCount(): Int {
        return 3
    }

    override fun getItem(position: Int): Fragment {
        return when(position){
            0 -> ButtonsFragment()
            1 -> TempFragment()
            else -> HumidityFragment()
        }
    }
}