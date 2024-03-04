package cn.lanqiao.unit;

import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;

import cn.lanqiao.GroupCompetition;


/**
 * ��Ԫ���ԣ�
 * 1. ��ʹ�� ����·���� �Ա���Դ�� GroupCompetition �� �е� grouping ������Ƶ�Ԫ����������
 * 2. �����·� GroupCompetitionTest ������д��Ԫ���Դ��롣
 * 3. ����·�������ֳƶ���·�����ԣ����ڳ��������ͼ�Ļ����ϣ�ͨ���������ƽṹ�Ļ�·�����ԣ�����������ִ��·�����ϣ��Ӷ���Ʋ��������ķ�����
 */


public class GroupCompetitionTest {
	static GroupCompetition group;

	@Before
	public void initGroupCompetition() {
		group = new GroupCompetition();
	}

	@Test
    public void test01() {
            assertEquals("�ٶ�A��", group.grouping(5, 87));
    }

    @Test
    public void test02() {
            assertEquals("�ٶ�B��", group.grouping(5, 79));
    }

    @Test
    public void test03() {
            assertEquals("������B��", group.grouping(13, 79));
    }

    @Test
    public void test04() {
            assertEquals("������A��", group.grouping(18, 87));
    }

    @Test
    public void test05() {
            assertEquals("�޸����ʸ�", group.grouping(20, 85));
    }

    @Test
    public void test06() {
            assertEquals("�޸����ʸ�", group.grouping(5, 52));
    }

}